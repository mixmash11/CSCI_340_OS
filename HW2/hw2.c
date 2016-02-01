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

// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//
//

int
main (int argc, char** argv)
{

  // ----------------------------------
  // Pseudocode
  // ----------------------------------
  //  Declare variables
  int done = FALSE; //Sets done value for primary for loop
  char* user_input = malloc (50);
  command_t pui;
  int runs = 1; // FIX

  //  INITIATE PARSED INPUT FIELDS
  pui.name = (char*) malloc (10);
  pui.argv = (char*) malloc (50);

  //  TEST PARSED INPUT

  //  pui.name = "Yo \0";
  //  pui.argc = 2;
  //  pui.argv = "Hi \0";
  //
  //  printf ("%s, %d, %s", pui.name, pui.argc, pui.argv);
  //  
  //  printf("Size check, size is %d", sizeof(pui.name));

  // while (!done)
  while (done != TRUE)
    {

      // print the prompt (i.e. >, #, or $ ... your choice)
      printf ("$ ");

      // read command line
      fgets (user_input, 50, stdin);
      printf ("\n");


      // DISPLAYS user_input THAT WAS JUST TYPED IN
      printf ("You entered: %s\n", user_input);

      // parse the command line
      parse (user_input, &pui);

      // if (parsed command is "exit")
      //    done = true

      // increments runs by one to trigger exit from loop.
      runs++;


      if (runs > 3) //FIX
        {
          printf ("  OUT IS TRUE \n");
          done = TRUE;
        }
      // else if (is _builtin(...))
      //        do_builtin(...)
      // else if (find_fullpath(...))
      //    execute(...)
      // else
      //    error()
      // cleanup(...)
      //

    }



  printf ("CSCI 340 Homework Assignment 2 - Have Fun!\n");

  return 0;

} // end main function
