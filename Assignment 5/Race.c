#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>


/*
** Compile and run this program, and make sure you get the 'aargh' error
** message. Fix it using a pthread mutex. The one command-line argument is
** the number of times to loop. Here are some suggested initial values, but
** you might have to tune them to your machine.
** Debian 8: 100000000
** Gouda: 10000000
** OS X: 100000
** You will need to compile your program with a "-lpthread" option.
*/

#define NUM_THREADS 2

int i;
pthread_mutex_t lock;

void *foo (void *bar) {

    pthread_mutex_lock(&lock);

    printf("in a foo thread, ID %ld\n", (long) pthread_self());

    for (i = 0; i < *((int *) bar); i++) {
        int tmp = i;

        if (tmp != i) {
            printf ("aargh: %d != %d\n", tmp, i);
        }
    }

    pthread_mutex_unlock(&lock);

    pthread_exit ((void *)pthread_self());

}

int main(int argc, char **argv)
{
    if(pthread_mutex_init(&lock, NULL) != 0){
        perror("mutex_init");
        return(1);
    }

    if (argc < 2) {
        printf("You must supply a numerical argument.\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);
    assert(errno == 0);
    assert(iterations > 0);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, foo, (void *) &iterations)) {
            perror ("pthread_create");
            return (1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        void *status;
        if (pthread_join (threads[i], &status)) {
            perror ("pthread_join");
            return (1);
        }
        printf("joined a foo thread, number %ld\n", (long) status);
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_mutex_destroy(&lock);

    return (0);
}
