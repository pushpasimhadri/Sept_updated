/*********************************************************************************************
 *@file:       array_registers.h
 *
 *@Created:    03-06-2024
 *
 *@brief:      This file implements to perform read/write operations on registers.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/

/* Header Files */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <fcntl.h> // for open
#include <errno.h> // for error codes

// Define the number of registers
#define NUM_REGISTERS   4

/* Macros */
#define DIR_SUCCESS     0
#define DIR_FAILURE    -1

struct registers_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
    unsigned int delay_value;
};

/*Function name:
 *    access_registers_main - This function perform 8,16,32 bit write and read operations on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read/write successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the driver failed to open, unable to perform read/write operations, it will return DIR_FAILURE
 */
int access_registers_main();

/*Function name:
 *    write_registers - This function perform 8,16,32 bit write operation on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data write successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the data unable to write, it will return DIR_FAILURE
 */
int write_registers(struct mem *obj_mem, int hFile);

/*Function name:
 *    read_registers - This function performs 8,16,32 bit read operation on the given registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the data failed to read, it will return DIR_FAILURE
 */
int read_registers(struct mem *obj_mem, int hFile);

/*Function name:
 *    delay_1ms - This function implemented for 1ms delay.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 * 	None
 */
void delay_1ms(void);

