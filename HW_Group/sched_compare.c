#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()

#include "procs.h"
#include "procheap.h"

// DO NOT CHANGE THESE TWO CONSTANTS !
#define INTER_ARRIVAL_TIME 3   // mean poisson dist
#define SERVICE_TIME       5   // mean poisson dist

#define TRUE 1
#define FALSE 0

double fcfs(proc_t *proc) {

    return proc->arrival_time;
}

double spn(proc_t *proc) {

    return proc->service_time;
}

double hrrn(proc_t *proc) {
    double numerator = proc->wait_time + proc->service_time;
    double denominator = proc->service_time;
    double hrrn = numerator / denominator;
    
    return hrrn;
}

void proc_copy(proc_t *original, proc_t *copy) {
    copy->arrival_time = original->arrival_time;
    copy->service_time = original->service_time;
    copy->wait_time = original->wait_time;
}

int is_taken(proc_t *procs) {

    int taken = FALSE;

    if (procs->wait_time == 1) {

        taken = TRUE;

    }

    return taken;
}

int heap_empty() {

    if (heap_size() < 1) {

        return TRUE;

    } else {

        return FALSE;

    }

}

int array_fully_used(const proc_t *procs, int numprocs) {
    int i;
    int proc_used = TRUE;
    for (i = 0; i < numprocs; i++) {
        if (procs[i].wait_time != 1) {
            proc_used = FALSE;
        }
    }
    return proc_used;
}

int main(int argc, char** argv) {
    int numprocs, seed;
    double total_time = 0;
    proc_t *procs; // array of procs with service time and arrival time
    int i;
    proc_t *check_proc;
    proc_t *heap_proc = malloc(sizeof (proc_t));
    int taken = FALSE;

    if (argc < 3) {
        fprintf(stderr, "USAGE: %s numprocs seed\n", argv[0]);
        return 1;
    }

    numprocs = atoi(argv[1]);
    seed = atoi(argv[2]);

    // create an array of numprocs randomly generate (arrival time, service time)
    procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);

    // Uncomment the next block of code and comment the line above if
    // you want to read the input from a file instead of generating
    // random values. This can be useful for debugging your code with
    // known inputs.  The file, "book_example.txt", contains an example
    // from the book.

    /*
    if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
      fprintf(stderr, "Error reading procs array\n");
      return 2;
    }
     */
//    printf("Check 1\n");
//    printf("procs array:\n");
//    printf("(arrival time, service time)\n");
    procs_print(procs, numprocs);

    //    printf("Check 2\n");
    //
    //    /* Either call your implemented functions for performing FCFS, SPN,
    //       and HRRN, or insert your code here to perform these algorithms.
    //       My recommendation is to write one or more functions for these
    //       algorithms in order for your main to be more readable and
    //       manageable.
    //     */
    printf("FCFS\n\n");
    //    
    //    
    //    // initialize heap
    heap_init(numprocs, fcfs);
    //    //printf("Check 3\n");
    //    
    //    
    while ((array_fully_used(procs, numprocs) == FALSE || taken == FALSE) || heap_empty() == FALSE) {
        printf("CURRENT TIME: %3.0f\n", total_time);
        //printf("Check 4\n");

        for (i = 0; i < numprocs; i++) {
            check_proc = &procs[i];
            if (is_taken(check_proc) == FALSE && total_time >= check_proc->arrival_time) {
                proc_copy(check_proc, heap_proc);
                heap_proc->wait_time = total_time - heap_proc->arrival_time;
                heap_insert(heap_proc);
                check_proc->wait_time = 1;

                printf("    Process %i added.\n", i);

                taken = TRUE;
            }
        }

        //printf("Check 5\n");

        if (heap_empty() == TRUE) {
            total_time += 1;
            heap_age(1);
        } else {
            check_proc = heap_deletemin();
            total_time += check_proc->service_time;
            heap_age(check_proc->service_time);

            printf("    Executing process \n");
            printf("        Service Time: %2.0f\n", check_proc->service_time);


        }

        //printf("Check 6\n");
    }

    printf("SPN\n\n");

    heap_free();
    procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
    total_time = 0;
    taken = FALSE;

    heap_init(numprocs, spn);
    //printf("Check 3\n");


    while ((array_fully_used(procs, numprocs) == FALSE || taken == FALSE) || heap_empty() == FALSE) {
        printf("CURRENT TIME: %3.0f\n", total_time);
        //printf("Check 4\n");

        for (i = 0; i < numprocs; i++) {
            check_proc = &procs[i];
            if (is_taken(check_proc) == FALSE && total_time >= check_proc->arrival_time) {
                proc_copy(check_proc, heap_proc);
                heap_proc->wait_time = total_time - heap_proc->arrival_time;
                heap_insert(heap_proc);
                check_proc->wait_time = 1;

                printf("    Process %i added.\n", i);

                taken = TRUE;
            }
        }

        //printf("Check 5\n");

        if (heap_empty() == TRUE) {
            total_time += 1;
            heap_age(1);
        } else {
            check_proc = heap_deletemin();
            total_time += check_proc->service_time;
            heap_age(check_proc->service_time);

            printf("    Executing process \n");
            printf("        Service Time: %2.0f\n", check_proc->service_time);


        }

        //printf("Check 6\n");
    }

    printf("HRRN\n");

    heap_free();
    procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
    total_time = 0;
    taken = FALSE;

    heap_init(numprocs, hrrn);
//    printf("Check 3\n");


    while ((array_fully_used(procs, numprocs) == FALSE || taken == FALSE) || heap_empty() == FALSE) {
        printf("CURRENT TIME: %3.0f\n", total_time);
//        printf("Check 4\n");

        for (i = 0; i < numprocs; i++) {
//            printf("Check 4a %i\n", i);
            check_proc = &procs[i];
//            printf("Check 4b %i\n", i);
            if (is_taken(check_proc) == FALSE && total_time >= check_proc->arrival_time) {
                proc_copy(check_proc, heap_proc);
//                printf("Check 4c %i\n", i);
                heap_proc->wait_time = total_time - heap_proc->arrival_time;
                printf("HRRN ALG OUTPUT: %2.2f\n", hrrn( heap_proc));
                heap_insert(heap_proc);
//                printf("Check 4d %i\n", i);
                check_proc->wait_time = 1;
//                printf("Check 4e %i\n", i);

                printf("    Process %i added.\n", i);

                taken = TRUE;
            }
        }

//        printf("Check 5\n");

        if (heap_empty() == TRUE) {
            total_time += 1;
            heap_age(1);
        } else {
            check_proc = heap_deletemin();
            total_time += check_proc->service_time;
            heap_age(check_proc->service_time);

            printf("    Executing process \n");
            printf("        Service Time: %2.0f\n", check_proc->service_time);


        }

//        printf("Check 6\n");
    }

//    printf("Check 7\n");
    free(procs); // procs array was dynamically allocated, so free up

    return 0;
}
