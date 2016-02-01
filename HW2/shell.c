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

void
parse (char* line, command_t* p_cmd)
{
  int line_iterator = 0; // for line pointer movement by character
  int word_count = 0; //counts words present
  int word_length = 0; //counts length of the word
  char* current_string = (char *) malloc (40); // current string being read
  int pcws = TRUE; // previous character was space boolean

  
  printf("Parse method started.\n");
  printf ("Parse recieved: %s", line);

  //LINE IS NULL
  if (line[0] == '\n')
    {
      printf ("Line is null\n");

      p_cmd->name = NULL;
      p_cmd->argc = 0;
      p_cmd->argv[0] = NULL;

      return;
    }

  //  LINE BEGINS WITH A SPACE (THROWS AN ERROR)
  if (line[0] == ' ')
    {
      fprintf (stderr, "ERROR:\n      Command can not begin with a space character.\n");
      exit (1);
    }

  printf ("Line is not null\n");



  // BEGIN: SPLITTING LINE INTO SMALLER STRINGS
  // Runs thru the line, character by character
  while (line[line_iterator] != '\n')
    {
      printf ("\n\nCURRENT CHARACTER:\n  %c", line[line_iterator]);

      //Check if a blank character, if so, move on and signal a space
      while (line[line_iterator] == ' ')
        {
          line_iterator++;
          if (line[line_iterator] != '\n')
            {

              printf ("  Previous character was a space.");
              printf ("  End of string reached.");

              // GOTO END OF STRING SCRIPT

            }
          pcws = TRUE;
          printf ("\n\nCURRENT CHARACTER:\n  %c", line[line_iterator]);
        }

      // A non-whitespace or carriage return character has been reached after a space
      if (pcws == TRUE)
        {
          printf ("  Previous character was a space.");

          pcws = FALSE; // Reset the pcws boolean

          word_count++;

          if (word_count > 1)
            {
              current_string[word_length] = '\0';
              printf ("\nCompleted word is %s\n", current_string);
              printf ("  Length of string is %d", word_length);

              //INSERT STRING INTO ARGUMENT ARRAY
              p_cmd->argv[word_count - 2] = (char *) malloc (word_length + 1);
              p_cmd->argv[word_count - 2] = current_string;

              printf ("\n-------------\n");
              printf ("argv[%d] set: %s", word_count - 2, p_cmd->argv[word_count - 2]);
              printf ("\n-------------\n");

              if (word_count == 2)
                {
                  //INSERT FIRST STRING INTO COMMAND STRING
                  p_cmd->name = (char *) malloc (word_length + 1);
                  p_cmd->name = current_string;

                  printf ("\n-------------\n");
                  printf ("cmd name set: %s", p_cmd->name);
                  printf ("\n-------------\n");
                }

            }

          word_length = 0;

        }

      current_string[word_length] = line[line_iterator];
      word_length++;

      line_iterator++;
    }

  if (pcws == FALSE)
    {
      word_count++;

      if (word_count > 1)
        {
          current_string[word_length] = '\0';
          printf ("\nCompleted word is %s\n", current_string);
          printf ("  Length of string is %d", word_length);

          //INSERT STRING INTO ARGUMENT ARRAY
          p_cmd->argv[word_count - 2] = (char *) malloc (word_length + 1);
          p_cmd->argv[word_count - 2] = current_string;

          printf ("\n-------------\n");
          printf ("argv[%d] set: %s", word_count - 2, p_cmd->argv[word_count - 2]);
          printf ("\n-------------\n");

          if (word_count == 2)
            {
              //INSERT FIRST STRING INTO COMMAND STRING
              p_cmd->name = (char *) malloc (word_length + 1);
              p_cmd->name = current_string;

              printf ("\n-------------\n");
              printf ("cmd name set: %s", p_cmd->name);
              printf ("\n-------------\n");
            }

        }
    }


  p_cmd->argc = word_count - 1;
  printf ("\n-------------\n");
  printf ("argc set: %d", p_cmd->argc);
  printf ("\n-------------\n");

  // END: SPLITTING LINE INTO SMALLER STRINGS

  printf ("End of string reached.");

}

// int execute(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// void cleanup(command_t* p_cmd);
