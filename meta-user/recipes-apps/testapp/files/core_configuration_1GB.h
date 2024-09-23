/*********************************************************************************************
 *@file:       core_configuration_1GB.h
 *
 *@Created:    22-08-2024
 *
 *@brief:      This file implements to configure the core by performing write operation.
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

/* Structure to store memory operation details */
struct conf_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

/* Function: Core_configuration_main
 * ------------------------
 * This function performs the fixed 32-bit write operation on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is written successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform write operation, it will return DIR_FAILURE.
 */
int core_conf_main(void);
