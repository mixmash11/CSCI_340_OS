// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------

// get the next token starting from line.  Return length of token.

int get_next_token(char* line, char** token) {
    int i; // for loop control variable
    int start; // start of some non-white space block
    int inwhite = TRUE; // TRUE if "in" white space

    // go through the string one character at a time
    for (i = 0; line[i] != '\0'; i++) { // NOTE:  i incremented ONLY here!
        if (iswhite(line[i])) { //   did we find a white space?
            if (!inwhite) { //   if not already in white space
                break; //       then we got a new token
            }
            inwhite = TRUE; //   remember the state that we are in white space
        } else { // not a white space character (ie. an argument)
            if (inwhite) { // remember where we transitioned from a white
                start = i; //   to non-white region
            }
            inwhite = FALSE; // we are now not in a white space state
        }
    }

    if (!inwhite) { // if we didn't end with a white space
        *token = line + start; //     then we got a new token
        return i - start;
    }

    *token = NULL; // if we get here, no tokens available
    return 0;
}

int count_tokens(char* line) {
    int num_tokens = 0;
    char *token;
    int length = get_next_token(line, &token);

    while (length > 0) {
        num_tokens++;
        line = token + length;
        length = get_next_token(line, &token);
    }

    return num_tokens;
}

void parse(char* line, command_t* p_cmd) {
    int i;
    int length;
    char *token;

    // get number of command line arguments
    p_cmd->argc = count_tokens(line);

    if (p_cmd->argc > 0) {
        // allocate space for arguments array (+ 1 for NULL)
        p_cmd->argv = (char **) malloc((p_cmd->argc + 1) * sizeof (char *));

        for (i = 0; i < p_cmd->argc; i++) { // for each argument...
            length = get_next_token(line, &token);
            line = token + length;
            p_cmd->argv[i] = (char *) malloc(length + 1);
            my_strncpy(p_cmd->argv[i], token, length);
        }
        p_cmd->argv[i] = NULL;
    } else { // blank line entered
        p_cmd->argv = (char **) malloc(2 * sizeof (char *));
        p_cmd->argv[0] = (char *) malloc(1);
        p_cmd->argv[0][0] = '\0';
        p_cmd->argv[1] = NULL;
    }
    // allocate space and copy argv[0] into name
    p_cmd->name = (char *) malloc(my_strlen(p_cmd->argv[0]) + 1);
    my_strncpy(p_cmd->name, p_cmd->argv[0], my_strlen(p_cmd->argv[0]));
}

int execute(command_t* p_cmd) {

    int child_process_status;
    int cpid1, cpid2;
    int fds[2];
    int status;
    char fullpath[MAXSTRLEN];
    char fullpath1[MAXSTRLEN];
    char fullpath2[MAXSTRLEN];

    int pipe_loc;

    char* init_cmd_str;
    command_t init_cmd;
    int init_cmd_len = 0;

    char* pipe_cmd_str;
    command_t pipe_cmd;
    int pipe_cmd_len = 0;
    
    int iterator;

    pipe_loc = has_pipe(p_cmd);

    if (pipe_loc == 0) {

        if ((cpid1 = fork()) == 0) {
            find_fullpath(fullpath, p_cmd);
            execv(fullpath, p_cmd->argv);
            perror("Execute terminated with an error condition!\n");
            exit(1);
        }

    } else {

        //printf("Pipe branch\n");

        // Count size for first command
        for (iterator = 0; iterator < pipe_loc; iterator++) {
            init_cmd_len = init_cmd_len + my_strlen(p_cmd->argv[iterator]) + 1;

        }
        init_cmd_str = (char *) malloc(init_cmd_len);

        // Concatenate first command
        for (iterator = 0; iterator < pipe_loc; iterator++) {
            my_strncat(init_cmd_str, p_cmd->argv[iterator], my_strlen(p_cmd->argv[iterator]));
            my_strncat(init_cmd_str, " ", 1);
        }

        //printf("Init cmd:\n     %s\n", init_cmd_str);

        // Count size for second command
        for (iterator = pipe_loc + 1; iterator < p_cmd->argc; iterator++) {
            pipe_cmd_len = pipe_cmd_len + my_strlen(p_cmd->argv[iterator]) + 1;

        }
        pipe_cmd_str = (char *) malloc(pipe_cmd_len);

        // Concatenate second command
        for (iterator = pipe_loc + 1; iterator < p_cmd->argc; iterator++) {
            my_strncat(pipe_cmd_str, p_cmd->argv[iterator], my_strlen(p_cmd->argv[iterator]));
            my_strncat(pipe_cmd_str, " ", 1);
        }

        //printf("Pipe cmd:\n     %s\n", pipe_cmd_str);
        
        parse(init_cmd_str, &init_cmd);
        find_fullpath(fullpath1, &init_cmd);
        parse(pipe_cmd_str, &pipe_cmd);
        find_fullpath(fullpath2, &pipe_cmd);

        pipe(fds);
        
        if (cpid1 = fork() == 0) {
            close(1);
            dup(fds[1]);
            close(fds[0]);
            
            execv(fullpath1, init_cmd.argv);
            //perror("Execute terminated with an error condition!\n");
        }
        
        if (cpid2 = fork() == 0) {
            close(0);
            dup(fds[0]);
            close(fds[1]);
            
            execv(fullpath2, pipe_cmd.argv);
            //perror("Execute terminated with an error condition!\n");
        }
        close(fds[0]);
        close(fds[1]);
        waitpid(cpid1, &child_process_status, 0);
        waitpid(cpid2, &child_process_status, 0);
        return 0;

    }

    return wait(&status);
}

int find_fullpath(char* fullpath, command_t* p_cmd) {
    int i;
    int start = 0;
    char dir[MAXSTRLEN]; // directory stripped from PATH
    char *mypathvar; // copy of string returned by getenv("PATH")
    struct stat sb; // for stat() call
    char *pathvar = getenv("PATH");
    int pathvarlen = my_strlen(pathvar);

    // allocate space for pathvar (+ appending a colon and null character)
    // copy pathvar into mypathvar with extra colon appended
    // this allows all processing to occur within the loop
    mypathvar = (char *) malloc(pathvarlen + 2);
    my_strncpy(mypathvar, pathvar, pathvarlen);
    mypathvar[pathvarlen] = ':';
    mypathvar[pathvarlen + 1] = '\0';

    for (i = 0; mypathvar[i] != '\0'; i++) {
        if (mypathvar[i] == ':') {
            my_strncpy(dir, mypathvar + start, i - start);
            start = i + 1;
            // build the fullpath string
            my_strncpy(fullpath, dir, MAXSTRLEN);
            my_strncat(fullpath, "/", MAXSTRLEN);
            my_strncat(fullpath, p_cmd->name, MAXSTRLEN);

            if (stat(fullpath, &sb) != -1 && S_ISREG(sb.st_mode)) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int is_builtin(command_t* p_cmd) {
    int i;

    for (i = 0; valid_builtin_commands[i] != NULL; i++) {
        if (my_strequal(p_cmd->name, valid_builtin_commands[i]))
            return TRUE;
    }
    return FALSE;
}

int do_builtin(command_t* p_cmd) {
    if (my_strequal(p_cmd->name, valid_builtin_commands[0]))
        return chdir(p_cmd->argv[1]);

    // can add more commands ...

    return SUCCESSFUL;
}

void cleanup(command_t* p_cmd) {
    int i;

    free(p_cmd->name);
    p_cmd->name = NULL;
    for (i = 0; i < p_cmd->argc; i++) {
        free(p_cmd->argv[i]);
        p_cmd->argv[i] = NULL;
    }
    free(p_cmd->argv);
    p_cmd->argv = NULL;
    p_cmd->argc = 0;
}

// **** MY UTILITY FUNCTIONS

int my_strlen(const char* s) {
    int count = 0;
    while (*s++ != '\0')
        count++;

    return count;
}

// assumes properly terminated strings

int my_strequal(const char *s, const char *t) {
    while (*s != '\0' && *s == *t) {
        s++;
        t++;
    }

    return *s == '\0' && *t == '\0';
}

int my_strncpy(char *dest, const char *src, int n) // copy dest to src
{
    while (*src != '\0' && n--) {
        *dest++ = *src++;
    }
    *dest = '\0';

    return 0;
}

int my_strncat(char *dest, const char *src, int n) // append dest to src
{
    while (*dest != '\0')
        dest++; // move to the end of dest

    while (*src != '\0' && n--) {
        *dest++ = *src++;
    }
    *dest = '\0';

    return 0;
}

int iswhite(char c) {
    return c == ' ' || c == '\t';
}

int has_pipe(command_t* p_cmd) {
    int arg_num;
    char* pipe_str = "|";

    for (arg_num = 0; arg_num < p_cmd->argc; arg_num++) {
        //printf("Argument is %s.\n", p_cmd->argv[arg_num]);

        if (my_strequal(p_cmd->argv[arg_num], pipe_str)) {
            //printf("Pipe found!\n");
            return arg_num;
        }
    }

    return 0;
}
