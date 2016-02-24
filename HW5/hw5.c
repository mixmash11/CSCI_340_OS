#include <stdio.h>         // for printf()
#include <pthread.h>       // for pthread_xxx() routines

#include "mcsim.h" // monte carlo simulation function prototypes

double gcount;    // global counter -- a double to handle large sums (billions+)
long numits;      // global variable for number of iterations (see step 3 below)

int main(int argc, char** argv)
{
  gcount = 0;

  /*

    ---------------------------------------------------------------------
    Step-by-Step procedure for Monte carlo simulator to estimate PI
    ---------------------------------------------------------------------
    1. Create the following variables:
       - pointer to an array of pthread structures
       - counting variables for loops
       - thread id
       - exit status of joined thread
       - number of threads to run
       - maximum number of threads (hint: rlimit)
       - nanosecond start and stop timespec structs
    2. Get number of threads input by user from argv[1]
    3. Get number of iterations input by user from argv[2]
    4. Get maximum number of threads the OS can create (man getrlimit function)
    5. If number of threads > maximum OS threads then goto 14, else goto step 6
    6. Allocate array of pthread structures using number of threads from step 2
    7. Get start time of simulation and store in timespec struct
    8. Create a pthread for each position in pthread array created in step 6
       - if an error occurs during thread creation exit simulation immediately
    9. Join each pthread created in the pthread array
       - if an error occurs during thread join exit simulation immediately
    10. Get stop time of simulation and store in timespec struct
    11. Print out:
       - value of PI using 6 decimal places
       - value stored in global variable gcount using 0 decimal places
       - time in seconds to run the simulation using 4 decimal places (hint: use mydifftime function)
    12. Free memory allocated for pthread array
    13. Call pthread terminate function (hint: pthread_exit function)
    14. exit simulation program

    ---------------------------------------------------------------------
    Example input and output of Monte carlo simulator to estimate PI
    ---------------------------------------------------------------------

    # ./hw5 300 100  // i.e. run simulatior using 300 threads and 100 iterations

    monte carlo value of PI = 3.141200
    value of count = 23559
    time in seconds = 0.0761
  */

  return 0;

} // end main function
