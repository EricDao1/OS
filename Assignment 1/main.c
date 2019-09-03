#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int result = fork();
    int status;
    int wait_pid = waitpid(result, &status, 0);

    if (result < 0) {
        perror("fork() error");
        exit(-1);
    }

    else if (result == 0) {
        printf("Child PID: %d\nParent PID: %d\n",  getpid(), getppid());
        execl("./counter", "./counter", "5", 0);
        perror("execl() failure! \n\n");
        printf("This print is after execl() and should not have been executed if execl were successful! \n\n");
        _exit(1);

    }

    else if(wait_pid < 0){
        perror("waitpid");
        exit(-1);
    }

    else {
        assert(wait_pid != 0);
        assert(WEXITSTATUS(status));
        assert(WIFEXITED(status));
        assert(printf("Process %d exited with status: %d\n", result, WEXITSTATUS(status)));
    }

    return 0;

}
