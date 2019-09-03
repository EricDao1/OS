#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//Got help from Dr. Beatys

void handler(int sig){
    const char *signal_name;
    switch (sig) {
        case SIGUSR1:
            signal_name = "SIGUSR1";
            break;
        case SIGUSR2:
            signal_name = "SIGUSR2";
            break;
        case SIGHUP:
            signal_name = "SIGHUP";
            break;
        default:
            fprintf(stderr, "Caught wrong signal: %d\n", sig);
            return;
    }

    assert (printf("Parent received: %s\n", signal_name));

}

int main(int argc, char* argv[]) {

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert (sigaction (SIGUSR1, &action, NULL) == 0);
    assert (sigaction (SIGUSR2, &action, NULL) == 0);
    assert (sigaction (SIGHUP, &action, NULL) == 0);

    if (sigaction(SIGUSR1, &action, NULL) < 0) {
        perror("sigaction()");
        exit(-1);
    }

    if (sigaction(SIGUSR2, &action, NULL) < 0) {
        perror("sigaction()");
        exit(-1);
    }

    if (sigaction(SIGHUP, &action, NULL) < 0) {
        perror("sigaction()");
        exit(-1);
    }

    pid_t result = fork();
    int status;
    int wait_pid = waitpid(result, &status, 0);


    if(result < 0){
        perror("fork() error");
        exit(-1);
    }

    else if(result == 0){
        execl("./child", "./child", NULL);
        perror("execl() failure! \n\n");
        exit(-1);

    }

    else if(wait_pid < 0){
        perror("waitpid");
        exit(-1);
    }

    else{
        assert(wait_pid != 0);
        assert(WIFEXITED(status));
    }

    return 0;

}
