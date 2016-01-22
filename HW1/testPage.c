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
  int string_iterator;
  int theta_iterator;
  int vector_iterator;
  double radius_in;
  double theta_in;
  v_struct *vector_array;

  vector_array = (v_struct*) malloc (sizeof (v_struct));
  vector_iterator = 0;

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
  while (!feof (vectorFile))
    {
      fgets (line_String, 40, vectorFile);
      //      printf ("String:\n     %s", line_String);

      //    iterator = 0;
      //    while(line_String[iterator] != '\0'){
      //        printf("Character %i: %c\n", iterator, line_String[iterator]);
      //        iterator++;
      //      }

      //  READ LINE INTO RADIUS VALUE
      //      printf ("     Reading radius...\n");
      string_iterator = 0;
      while (line_String[string_iterator] != ',')
        {

          //          printf ("Character %i: %c\n", iterator, line_String[iterator]);

          radius_String[string_iterator] = line_String[string_iterator];
          string_iterator++;
        }
      radius_String[string_iterator] = '\0'; // CLOSE RADIUS STRING
      string_iterator++; // MOVES TO CHARACTER AFTER COMMA

      //  READ LINE INTO THETA VALUE
      //      printf ("     Reading theta...\n");
      theta_iterator = 0;
      while (line_String[string_iterator] != '\0')
        {

          //          printf ("Character %i: %c\n", iterator, line_String[iterator]);

          theta_String[theta_iterator] = line_String[string_iterator];
          string_iterator++;
          theta_iterator++;
        }
      theta_String[theta_iterator] = '\0'; // CLOSE RADIUS STRING

      //      printf ("Radius is: %s\n", radius_String);
      //      printf ("Theta is: %s\n", theta_String);

      //  CONVERT VALUES TO FLOATS
      radius_in = atof (radius_String);
      theta_in = atof (theta_String);

      printf ("Radius is: %.2f, ", radius_in);
      printf ("Theta is: %.2f\n", theta_in);

      //  CHECK/CORRECT THETA VALUES
      while (theta_in > 360)
        {
          printf ("     Theta TOO HIGH: %.2f\n", theta_in);

          theta_in = theta_in - 360;

          printf ("Theta is: %.2f\n", theta_in);
        }
      while (theta_in < 0)
        {
          printf ("     Theta TOO LOW: %.2f\n", theta_in);

          theta_in = theta_in + 360;

          printf ("Theta is: %.2f\n", theta_in);
        }

      //  ENTER VALUES INTO VECTOR ARRAY
      vector_array[0].r = radius_in;
      vector_array[0].theta = theta_in;

      vector_iterator++;

    }

  //    while (vector_iterator >= 0){
  //        printf ("Vector %i radius is: %.2f\n", vector_iterator, radius_in);
  //        printf ("Vector %i theta is: %.2f\n", vector_iterator, theta_in);
  //        
  //        vector_iterator = vector_iterator - 1;
  //      }
  
  printf("Vector count is %i\n", vector_iterator);
  
  printf ("Vector %i radius is: %.2f\n", 0, radius_in);
  printf ("Vector %i theta is: %.2f\n", 0, theta_in);

  printf ("Closing file...\n");
  fclose (vectorFile);
  printf ("File closed...\n");

  printf ("End of Program\n");
  return 0;
}