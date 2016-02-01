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
// void parse(char* line, command_t* p_cmd);
void parse(char* line, command_t* p_cmd){
  int line_iterator = 0; // for line pointer iteration
  int word_count; //counts words present
  int word_length; //counts length of the word
  char* current_string; // current string being read
  
  
  printf("Parse recieved: %s", line);
  
  if (line[0] == '\n'){
      printf("Line is null\n");
      
      p_cmd->name = NULL;
      p_cmd->argc = 0;
      p_cmd->argv[0] = NULL;
     
      return;
    }
  
    if (line[0] == ' '){
      fprintf (stderr, "ERROR:\n      Command can not begin with a space character.\n");
      exit (1);
    }
  
  printf("Line is not null\n");
  word_count++;
  
  while (line[line_iterator] != '\n'){
      
      if (line[line_iterator] == ' ') {
          word_count++;
          
          
          
        }
      
      
      
      
      line_iterator++;
    }
  
  
    
}

// int execute(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// void cleanup(command_t* p_cmd);
