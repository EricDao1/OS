#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mysys(x) { \
    (x); \
    int err = errno; \
    if (err) { \
        fprintf(stderr, "In file %s at line %d: ", __FILE__, __LINE__); \
        perror(#x); \
        exit(err);} \
    }

#define WRITESTRING(STRING) \
    mysys(write(STDOUT_FILENO, STRING, strlen(STRING)));

int eye2eh(int i, char *buffer, int buffersize, int base);

#define WRITEINT(INT, LEN) { char buf[LEN]; \
    mysys(eye2eh(INT, buf, LEN, 10)); WRITESTRING(buf); }