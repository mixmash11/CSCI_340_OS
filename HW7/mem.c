#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
 */
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration) {
    int mem_slot;
    int int_mem_slot;
    int contiguous = 0;
    int iterator;

    for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
        memory[mem_slot] = 2;
    }

//    // FIRST FIT
//    if (strategy == FIRSTFIT) {
//        for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
//            if (memory[mem_slot] == 0) {
//                contiguous = 1;
//                int_mem_slot = 1;
//                
//                while (contiguous > 0 && contiguous < size ){
//                    if(memory[mem_slot + int_mem_slot] == 0){
//                        contiguous++;
//                        int_mem_slot++;
//                    }
//                    else{
//                        contiguous = 0;
//                    }
//                }
//                if (contiguous == size){
//                    for (iterator = 0; iterator <=  int_mem_slot; iterator++){
//                        memory[mem_slot + iterator] = duration;
//                    }
//                }
//                
//            }
//        }
//    }


    return -1;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired() {
    int mem_slot;
    int units_transpired = 0;

    for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
        if (memory[mem_slot] > 0) {
            memory[mem_slot] -= 1;
        }
        if (memory[mem_slot] == 0) {
            units_transpired += 1;
        }

    }

    return units_transpired;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size) {
    int mem_slot;
    int fragment_count = 0;
    int contiguous = 0;

    for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
        if (memory[mem_slot] == 0) {
            if (contiguous == 0) {
                fragment_count++;
                contiguous++;
            } else if (contiguous > 0 && contiguous < frag_size) {
                contiguous++;
            } else {
                contiguous = 0;
            }
        } else {
            contiguous = 0;
        }
    }
    return fragment_count;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear() {
    int mem_slot;

    for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
        memory[mem_slot] = 0;
    }
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size) {
    memory = malloc(sizeof (dur_t) * size);
    mem_size = size;
}

/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free() {
    free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print() {
    int mem_slot;
    int new_line = 0;

    for (mem_slot = 0; mem_slot < mem_size; mem_slot++) {
        printf("| %i | ", memory[mem_slot]);
        new_line++;
        if (new_line > 4) {
            printf("\n");
            new_line = 0;
        }
    }
    printf("\n\n");
}
