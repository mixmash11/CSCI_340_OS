// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <stdio.h> // IO functions
#include <stdlib.h>  // atof function
#include <math.h> // math functions
#include "utils.h" // your own functions

// ----------------------------------------------
// Define constants
#define TOTAL_VECS 10 // constant that defines the total number 
// of vectors, i.e. magnitude,direction 
// pairs, in the vectors text file.

// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//		argv = array of argument values
//
//

int
main (int argc, char** argv)
{

  // --------------------------------
  // Steps to be performed


  //	1. Define variables (including arrays)
  v_struct *vector_array;
  char* fileName;
  int numVectors;
  int vector_Iterator;
  double x_comp;
  double y_comp;

  fileName = argv[1];
  vector_array = malloc (TOTAL_VECS * sizeof (v_struct));

  //	2. Using read() function in utils.h, read vectors defined in text file 
  //		- the location of the text file (i.e. vectors.txt) must be defined in argv[1]

  numVectors = read (fileName, vector_array);

  //  	3. Loop through array of vector structs and print to console:
  //		- vector magnitude (using only 2 decimal places)
  //		- vector direction (in radians using only 2 decimal places)
  //		- vector direction (in degrees using only 2 decimal places)
  //		- Using compute_x() function in utils.h, x component value (using only 2 decimal places)
  //		- Using compute_y() function in utils.h, y component value (using only 2 decimal places)
  //	    in the following format
  //		r = <value>, theta = <value> degrees, <value> radians, x_comp = <value>, y_comp = <value>
  //	    For example:
  //		r = 10.00, theta = 180.00 degrees, theta = 3.14 radians, x_comp = -10.00, y_comp = 0.00 

  for (vector_Iterator = 0; vector_Iterator < numVectors; vector_Iterator++)
    {
      
      printf("r = %.2f", vector_array[vector_Iterator].r);
      printf(", ");
      printf("theta = %.2f degrees", vector_array[vector_Iterator].theta);
      printf(", ");
      printf("theta = %.2f radians", ((vector_array[vector_Iterator].theta) * PI / 180.0 ) );
      printf(", ");
      
      x_comp = x_component(&vector_array[vector_Iterator]);
      printf("x_comp = %.2f", x_comp );
      printf(", ");
      
      
      y_comp = y_component(&vector_array[vector_Iterator]);
      printf("y_comp = %.2f\n", y_comp );
      
    }

  printf (" Homework Assignment 1 - Have fun!\n");

  return 0;

} // end main() function
