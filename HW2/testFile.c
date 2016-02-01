#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

int
main (int argc, char** argv)
{


  char* line = "the end -f\n\0";

  int line_iterator = 0; // for line pointer movement by character
  int word_count = 0; //counts words present
  int word_length = 0; //counts length of the word
  char* current_string = (char *) malloc (40); // current string being read
  int pcws = TRUE; // previous character was space boolean

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

              //INSERT STRING INTO ARGUMENT ARRAY HERE
              // REMEMBER TO MALLOC HERE

              if (word_count == 2)
                {
                  //INSERT FIRST STRING INTO COMMAND STRING HERE
                  // REMEMBER TO MALLOC HERE
                }

            }

          word_length = 0;

        }

      current_string[word_length] = line[line_iterator];
      word_length++;

      line_iterator++;
    }

  word_count++;

  if (word_count > 1)
    {
      current_string[word_length] = '\0';
      printf ("\nCompleted word is %s\n", current_string);
      printf ("  Length of string is %d\n", word_length);

      //INSERT STRING INTO ARGUMENT ARRAY HERE
      // REMEMBER TO MALLOC HERE

      if (word_count == 2)
        {
          //INSERT FIRST STRING INTO COMMAND STRING HERE
          // REMEMBER TO MALLOC HERE
        }

    }




  printf ("End of string reached.");

  return 0;
}
