/****************************************************************************
 * @file:        core_read.c
 * 
 * @Created:     21-08-2024
 *
 * @brief:       This file implemented to read the status from the core by 
 * 		 performing 32bit read operation.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "core_read.h"

unsigned int read_32[] = {
    0x800C0008, 0x800C000C, 0x800C0010, 0x800C0014, 0x800C0018, 0x800C001C,
    0x800C0020, 0x800C0024, 0x800C0028, 0x800C002C, 0x800C0030, 0x800C0034,
    0x800C0038, 0x800C003C, 0x800C0040, 0x800C0044, 0x800C0048, 0x800C0004,
};

#define NUM_READ_32BIT  (sizeof(read_32) / sizeof(read_32[0]))

/*Function name:
 *    read_main - This function perform 32 bit read operation on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the driver failed to open, unable to perform read operation, it will return DIR_FAILURE
 */
int read_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    uint32_t l_result;
    struct read_mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_RDONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        DIR_ERRLOG("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    DIR_LOG("Opened /dev/ModuleDiagnostic\n");

    for (size_t i = 0; i < NUM_READ_32BIT; i++) {
        s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
        s_obj_mem.address = read_32[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            DIR_ERRLOG("32-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        
            DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, l_result);
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
