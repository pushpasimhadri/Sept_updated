#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

/* Macros */
#define Driver_path "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1

/* Operation codes */
#define OP_16BIT_READ      2
#define OP_32BIT_READ      3
#define OP_16BIT_WRITE     5
#define OP_32BIT_WRITE     6

/* Structure to store memory operation details */
struct mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

/* Function declaration */
int axi_main(void);



