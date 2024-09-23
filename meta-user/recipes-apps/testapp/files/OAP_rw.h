/*********************************************************************************************
 *@file:       core_write.h
 *
 *@Created:    21-08-2024
 *
 *@brief:      This file implements to perform 32-bit write operation on registers.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

/* Macros */
#define Driver_path        "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1
#define DIR_LOG            printf         /* Macro for information messages */
#define DIR_ERRLOG         printf         /* Macro for error messages */

/* Operation codes */
#define OP_32BIT_WRITE     6
#define OP_32BIT_READ      3

/* Structure to store memory operation details */
struct mem_seq {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

int OAP_read_write_seq(void);

