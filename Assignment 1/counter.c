#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <errno.h>
#include <assert.h>

int main(int argc, char* argv[]) {

    assert(argc == 2);

    int i;

    long num = strtol(argv[1], NULL, 10);

    for (i = 1; i < num + 1 ; i++){
        printf("Process: %d %d\n", getpid(), i);
    }

    return num;

}



