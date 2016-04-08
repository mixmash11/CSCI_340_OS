#include "dpsim.h"
#include <signal.h>


static const unsigned int NUM_PHILOSPHERS = 5;
static const unsigned int NUM_CHOPSTICKS = 5;

static int chopsticks[5];
static pthread_mutex_t mutex[5];
static pthread_t philosphers[5];
int deadlock_condition[5];

void print_eating() {
    int i;
    int eat = 0;
    printf("Philosopher(s) ");
    for (i = 0; i < NUM_CHOPSTICKS; i++) {
        if (chopsticks[i] == i && chopsticks[i + 1] == i) {
            printf("%i ", i);
            eat = 1;
        }
    }
    if (eat == 1) {
        printf("are eating\n");
    }
    else {
        __fpurge(stdout);
    }
}

int deadlock_check() {
    int i;
    int deadlock = 0;

    //printf("    DL RUN\n");
    for (i = 0; i < NUM_CHOPSTICKS; i++) {
        if (chopsticks[i] != i) {
            deadlock = 1;
        }
    }

    //deadlock = memcmp(chopsticks, deadlock_condition, sizeof (chopsticks));
    //    printf("DL condition: %i\n", deadlock);
    return deadlock;
}

void* th_main(void* th_main_args) {
    int i;
    int deadlock = -1;

    //printf("th_main\n");

    for (i = 0; i < NUM_CHOPSTICKS; i++) {
        chopsticks[i] = -1;
        deadlock_condition[i] = i;
    }

    for (i = 0; i < NUM_PHILOSPHERS; i++) {

        if (pthread_create(&philosphers[i], NULL, th_phil, i)) {
            perror("ERROR creating thread.");
            exit(1);
        }

    }

    while (TRUE) {
        //printf("DL INIT\n");
        deadlock = deadlock_check();

        if (deadlock == 0) {
            perror("Deadlock condition (0,1,2,3,4) ... terminating\n");
            break;
        }

        print_eating();__fpurge(stdout);
    }

    for (i = 0; i < NUM_PHILOSPHERS; i++) {
        pthread_kill(&philosphers[i], 9);

    }
    pthread_exit(0);

    return(0);



} // end th_main function

void* th_phil(void* th_phil_args) {
    int philosopher_number = th_phil_args;

    //printf("TH_PHIL\n     %i\n", philosopher_number);

    while (TRUE) {

        //printf("Philosopher %i\n", th_phil_args);

        delay(20000);
        eat(philosopher_number);
    }

} // end th_phil function

void delay(long nanosec) {

    struct timespec t_spec;

    t_spec.tv_sec = 0;
    t_spec.tv_nsec = nanosec;

    nanosleep(&t_spec, NULL);

} // end think function

void eat(int phil_id) {
    int right_fork = phil_id;
    int left_fork = phil_id + 1;

    if (left_fork > 4) {
        left_fork = 0;
    }

    pthread_mutex_lock(&mutex[right_fork]);
    chopsticks[right_fork] = phil_id;
    //printf("P%i has chopstick %i\n",phil_id,phil_id);
    //printf("    LEFT FORK IS %i\n", left_fork);
    delay(20000);


    pthread_mutex_lock(&mutex[left_fork]);
    chopsticks[left_fork] = phil_id;
    //printf("P%i has chopstick %i\n",phil_id,left_fork);

    //        pthread_mutex_lock(&eat_check);
    //        print_eating();
    //        pthread_mutex_unlock(&eat_check);
    delay(20000);

    pthread_mutex_unlock(&mutex[left_fork]);
    chopsticks[left_fork] = -1;

    pthread_mutex_unlock(&mutex[right_fork]);
    chopsticks[right_fork] = -1;


} // end eat function



