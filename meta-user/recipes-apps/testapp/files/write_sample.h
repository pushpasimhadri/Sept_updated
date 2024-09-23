#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define Driver_path "/dev/ModuleDiagnostic"
#define DIR_FAILURE -1
#define DIR_SUCCESS 0
#define OP_32BIT_WRITE 6

struct write_sample_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

int write_sample_main();
