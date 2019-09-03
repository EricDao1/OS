#include "syscall.h"
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <err.h>
#include <errno.h>

int status;

void handler() {

    if (wait(&status) < 0){
        perror("wait()");
    }
    if (SIGCHLD) {

        assert(wait(&status) != 0);
        assert(WIFSIGNALED(status));
        assert(WTERMSIG(status));
        WRITESTRING("Child's Status: ")
        WRITEINT(WEXITSTATUS(status), 14)
        exit(EXIT_SUCCESS);
    }

}

int main(int argc, char* argv[]) {

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    assert (sigaction(SIGCHLD, &action, NULL) == 0);

    if (sigaction(SIGCHLD, &action, NULL) < 0) {
        perror("sigaction()");
        exit(-1);
    }


    pid_t result = fork();
    int i;

    if (result < 0) {
        perror("fork() error");
        exit(-1);
    }

    else if(result == 0){
        execl("./child", "./child", NULL);
        perror("execl() failure! \n\n");
        exit(-1);
    }


    else{
        for (i = 0; i <= 5; i++) {
            WRITESTRING("Parent is going to SIGSTOP child.\n")
            kill(result, SIGSTOP);
            sleep(2);

            WRITESTRING("Parent is going to SIGCONT child.\n")
            kill(result, SIGCONT);
            sleep(2);
        }

        WRITESTRING("Sending child SIGINT")
        kill(result, SIGINT);

    }

    pause();


    return 0;

}
