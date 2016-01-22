//TEST PAGE
#include <stdio.h> // IO functions
#include <stdlib.h>  // atof function
#include <math.h> // math functions
#include "utils.h" // your own functions

#define TOTAL_VECS 10

int
main (int argc, char** argv)
{
  //  VARIABLE DECLARATION
  FILE *vectorFile;
  char line_String[40];
  char radius_String[8];
  char theta_String[8];
  int iterator;
  int theta_iterator;

  //  BEGIN CODE 
  //  CHECK FILE WAS PASSED
  if (argv[1] == NULL)
    {
      fprintf (stderr, "ERROR:\n      No file given in arguments.\n");
      exit (1);
    }

  // OPEN FILE
  printf ("Opening file...\n");

  vectorFile = fopen (argv[1], "r");

  //  READ FILE
  printf ("Reading file...\n");

  //  READ LOOP
  fgets (line_String, 40, vectorFile);
  while (vectorFile != NULL)
    {
      printf ("String:\n     %s", line_String);

      //    iterator = 0;
      //    while(line_String[iterator] != '\0'){
      //        printf("Character %i: %c\n", iterator, line_String[iterator]);
      //        iterator++;
      //      }

      //  READ LINE INTO RADIUS VALUE
      printf ("     Reading radius...\n");
      iterator = 0;
      while (line_String[iterator] != ',')
        {

          printf ("Character %i: %c\n", iterator, line_String[iterator]);

          radius_String[iterator] = line_String[iterator];
          iterator++;
        }
      radius_String[iterator] = '\0'; // CLOSE RADIUS STRING
      iterator++; // MOVES TO CHARACTER AFTER COMMA

      //  READ LINE INTO THETA VALUE
      printf ("     Reading theta...\n");
      theta_iterator = 0;
      while (line_String[iterator] != '\0')
        {

          printf ("Character %i: %c\n", iterator, line_String[iterator]);

          theta_String[theta_iterator] = line_String[iterator];
          iterator++;
          theta_iterator++;
        }
      theta_String[theta_iterator] = '\0'; // CLOSE RADIUS STRING

      printf ("Radius is: %s\n", radius_String);
      printf ("Theta is: %s\n", theta_String);
      
      fgets (line_String, 40, vectorFile);
    }




  printf ("Closing file...\n");
  fclose (vectorFile);
  printf ("File closed...\n");

  printf ("End of Program\n");
  return 0;
}