/*********************************************************************************************
 *@file:       data_registers.h
 *
 *@Created:    06-08-2024
 *
 *@brief:      This file implements to read the status from the core and write into it.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

#define Driver_path           "/dev/ModuleDiagnostic"
#define DIR_FAILURE           -1
#define DIR_SUCCESS           0
#define DIR_LOG               printf         /* Macro for information messages */
#define DIR_ERRLOG            printf         /* Macro for error messages */
#define OP_32BIT_READ         3
#define OP_32BIT_WRITE        6
#define MAX_CATEGORIES 10
#define MAX_LINE_LENGTH 60

struct data_mem {
    int operation;
    unsigned int address;
    unsigned int value;
};

/*Function name:
 *    registerdata_main - This function implements to read the categories from the text file and perform read and write operations.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read from the text file and perform read and write operations successfully,function will return DIR_SUCCESS
 *      DIR_FAILURE - If the text file is failed to open, function will return DIR_FAILURE
 */
int registerdata_main(void);
