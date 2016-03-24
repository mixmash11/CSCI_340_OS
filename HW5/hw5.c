#include <stdio.h>         // for printf()
#include <pthread.h>       // for pthread_xxx() routines

#include "mcsim.h" // monte carlo simulation function prototypes

double gcount; // global counter -- a double to handle large sums (billions+)
long numits; // global variable for number of iterations (see step 3 below)

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

int main(int argc, char** argv) {
    int ret;
    long double pi;
    long double time;
    gcount = 0;
    //  1. Create the following variables:
    //       - pointer to an array of pthread structures
    pthread_t* thread_array;
    //       - counting variables for loops
    //       - thread id
    int pid;
    //       - exit status of joined thread
    void* retval;
    //       - number of threads to run
    int num_threads;
    //       - maximum number of threads (hint: rlimit)
    int max_threads;
    struct rlimit rlim;
    //       - nanosecond start and stop timespec structs
    struct timespec start_time;
    struct timespec stop_time;


    //  2. Get number of threads input by user from argv[1]
    //  3. Get number of iterations input by user from argv[2]
    num_threads = atoi(argv[1]);
    numits = atol(argv[2]);
    //    printf("\n\n\nThreads: %i, iterations: %i\n", num_threads, numits);

    //  4. Get maximum number of threads the OS can create (man getrlimit function)
    getrlimit(RLIMIT_NPROC, &rlim);
    max_threads = rlim.rlim_max;
    //    printf("Max number of threads: %i\n", max_threads);

    //  5. If number of threads > maximum OS threads then goto 14, else goto step 6
    if (num_threads > max_threads) {
        fprintf(stderr, "ERROR: Threads input exceeds maximum number of threads.\n");
        return -1;
    }

    //  6. Allocate array of pthread structures using number of threads from step 2
    thread_array = malloc(sizeof (pthread_t) * num_threads);
    //    printf("%i threads malloc'd\n", num_threads);

    //  7. Get start time of simulation and store in timespec struct
    clock_gettime(CLOCK_REALTIME, &start_time);
    //    printf("Start time is %li\n", start_time.tv_nsec);

    //  8. Create a pthread for each position in pthread array created in step 6
    //       - if an error occurs during thread creation exit simulation immediately
    for (pid = 0; pid < num_threads; pid++) {

        //        printf("\n\nCreating thread %i |", count1);
        ret = pthread_create(&thread_array[pid], NULL, th_routine, &numits);
        if (ret != 0) {
            fprintf(stderr, "ERROR: Thread creation error.\n");
            return -1;
        }
        //        printf(" Thread %i created.\n", count1);
    }

    //    9. Join each pthread created in the pthread array
    //     - if an error occurs during thread join exit simulation immediately
    for (pid = 0; pid < num_threads; pid++) {
        //        printf("\n\nJoining thread %i |", count1);
        ret = pthread_join(thread_array[pid], NULL);
        if (ret != 0) {

            fprintf(stderr, "ERROR: Thread join error.\n");
            return -1;
        }
        //        printf(" Thread %i joined.\n", count1);
    }
    //    10. Get stop time of simulation and store in timespec struct
    clock_gettime(CLOCK_REALTIME, &stop_time);
    //    printf("All threads joined.\n");

    //    11. Print out:
    //     - value of PI using 6 decimal places
    //     - value stored in global variable gcount using 0 decimal places
    //     - time in seconds to run the simulation using 4 decimal places (hint: use mydifftime function)

    //    printf("\n\n");
    pi = 4 * gcount / (numits * num_threads);
    printf("\nmonte carlo value of PI = %.6Lf\n", pi);
    printf("value of count = %.0f\n", gcount);
    time = mydifftime(&start_time, &stop_time)/1000000000;
    printf("time in seconds = %.4Lf\n", time);

    //    12. Free memory allocated for pthread array
    free(thread_array);

    //    13. Call pthread terminate function(hint : pthread_exit function)
    pthread_exit(&retval);

    //    14. exit simulation program
    return 0;

} // end main function
