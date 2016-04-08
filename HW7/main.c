#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
 */

int main(int argc, char** argv) {
    
    mem_init(10);
    mem_clear();
    mem_print();
    
    mem_allocate(FIRSTFIT, 1, 2);
    mem_print();
    
    mem_single_time_unit_transpired();
    mem_print();
    
    mem_single_time_unit_transpired();
    mem_print();
    
    printf("%i\n", mem_fragment_count(2));
    printf("%i\n", mem_fragment_count(3));
    printf("%i\n", mem_fragment_count(9));
    printf("%i\n", mem_fragment_count(10));
    
    

    return 0;
}
