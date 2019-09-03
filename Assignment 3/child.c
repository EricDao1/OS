#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int);


int main(int argc, char* argv[]) {


    for (;;) {

        printf("Awake in %d\n", getpid());
        sleep(1);
    }



    return 0;

}



