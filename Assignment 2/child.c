#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//Got help from Dr. Beatys

void handler(int);


int main(int argc, char* argv[]) {

    printf("Child: sending SIGUSR1\n");
    kill(getppid(), SIGUSR1);

    printf("Child: sending SIGUSR1\n");
    kill(getppid(), SIGUSR1);

    printf("Child: sending SIGUSR1\n");
    kill(getppid(), SIGUSR1);

    printf("Child: sending SIGUSR2\n");
    kill(getppid(), SIGUSR2);

    printf("Child: sending SIGHUP\n\n");
    kill(getppid(), SIGHUP);

    return 0;

}



