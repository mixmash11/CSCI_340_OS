#include <stdio.h>
#include "dpsim.h"

/**************************************************

Main Function:
        int main( int argc, char** argv )

------------------------------------------------
In this function perform the following steps:
------------------------------------------------
1. Create the following variables:
        - main_thread (pthread_t)
        - status (join status value)
2. Create a main_thread 
        - If the return value != 0, then display an error message and 
          immediately exit program with status value 1.
3. Join the main_thread
        - If the return value != 0, then display an error message and
          immediately exit the program with status value 2.
4. Display join status value.
5. Exit program.

 */

int main(int argc, char** argv) {
    
//    printf("%i\n", 1);
    
    static pthread_t main_thread;
    int* status;

//    printf("%i\n", 2);

    if (pthread_create(&main_thread, NULL, th_main, NULL)) {
        perror("ERROR creating thread.");
        return 1;
    }
    
//    printf("%i\n", 3);
    
    if (status = pthread_join(main_thread, NULL)) {
        perror("ERROR joining thread.");
        return 2;
    }
    
//    printf("%i\n", 4);

    return 0;

} // end main function