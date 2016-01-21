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
  char ex_string[10] = "file.txt";

  printf ("%s\n", ex_string);

  return 0;
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