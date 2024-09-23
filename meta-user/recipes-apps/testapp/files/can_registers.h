#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

/* Macros */
#define Driver_path "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1

/* Operation codes */
#define OP_32BIT_READ      3
#define OP_32BIT_WRITE     6
#define NUM_REGISTERS      3
/*
struct mem {
    unsigned int address;
    unsigned int value;
    int operation;
};
*/

struct registers_mem {
    uint32_t address;
    uint32_t value;
    int operation;
};

/* Function declaration */
int can_main(void);


