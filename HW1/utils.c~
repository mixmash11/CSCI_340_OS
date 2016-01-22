// -----------------------------------
// CSCI 340 - Operating Systems I 
// Spring 2015 (Tony Leclerc, Brent Munsell)
// utils.c implementation file
// Homework Assignment 1
//
// -----------------------------------

// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <stdio.h> // IO functions
#include <stdlib.h>  // atof function
#include <math.h> // math functions
#include "utils.h" // your own functions

// Now you put your implementation of the function prototypes here...

int
read (char* file_name, v_struct* p_vec_array)
{
  //  VARIABLE DECLARATION
  FILE *vectorFile;
  vectorFile = fopen (file_name, "r");
  char line_String[40];
  char radius_String[8];
  char theta_String[8];
  int string_iterator;
  int theta_iterator;
  int vector_iterator;
  double radius_in;
  double theta_in;

  vector_iterator = 0;

  //  BEGIN CODE 
  //  CHECK FILE WAS PASSED
  if (file_name == NULL)
    {
      fprintf (stderr, "ERROR:\n      No file given in arguments.\n");
      exit (1);
    }

  // OPEN FILE
  //  printf ("Opening file...\n");

  vectorFile = fopen (file_name, "r");

  //  READ FILE
  //  printf ("Reading file...\n");

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

      //      printf ("Radius is: %.2f, ", radius_in);
      //      printf ("Theta is: %.2f\n", theta_in);

      //  CHECK/CORRECT THETA VALUES
      while (theta_in > 360)
        {
          //          printf ("     Theta TOO HIGH: %.2f\n", theta_in);

          theta_in = theta_in - 360;

          //          printf ("Theta is: %.2f\n", theta_in);
        }
      while (theta_in < 0)
        {
          //          printf ("     Theta TOO LOW: %.2f\n", theta_in);

          theta_in = theta_in + 360;

          //          printf ("Theta is: %.2f\n", theta_in);
        }

      //  ENTER VALUES INTO VECTOR ARRAY
      p_vec_array[vector_iterator].r = radius_in;
      p_vec_array[vector_iterator].theta = theta_in;

      vector_iterator++;

    }

  //  for (vector_iterator = 0; vector_iterator < 10; vector_iterator = vector_iterator + 1 )
  //    {
  //      printf ("Vector %i radius is: %.2f\n", vector_iterator, p_vec_array[vector_iterator].r);
  //      printf ("Vector %i theta is: %.2f\n", vector_iterator, p_vec_array[vector_iterator].theta);
  //    }

  //  printf ("Closing file...\n");
  fclose (vectorFile);
  //  printf ("File closed...\n");
  return (vector_iterator - 1 );
}

double
x_component (v_struct* p_vector)
{
  double theta_radians;
  double x_component = 0.0;

  theta_radians = (p_vector[0].theta * PI) / 180.0;

  x_component = p_vector[0].r * cos (theta_radians);

  return x_component;
}

double
y_component (v_struct* p_vector)
{
  double theta_radians;
  double y_component = 0.0;

  theta_radians = (p_vector[0].theta * PI) / 180.0;

  y_component = p_vector[0].r * sin (theta_radians);

  return y_component;
}