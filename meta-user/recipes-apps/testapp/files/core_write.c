/****************************************************************************
 * @file:        core_write.c
 * 
 * @Created:     21-08-2024
 *
 * @brief:       This file implemented to write the status to the core by 
 *               performing 32bit write operation.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "core_write.h"

unsigned int write_32BIT[] = {
        0x80040008, 0x8004000C, 0x80040010, 0x80040014, 0x80040018, 0x8004001C, 0x80040020,
        0x80040024, 0x80040028, 0x8004002C, 0x80040030, 0x80040034, 0x80040038, 0x8004003C,
        0x80040040, 0x80040044
};

unsigned int data_to_write_32BIT[] = {
        0x003C0000, 0x03000000, 0x72A70200, 0x00032A20, 0x08004500, 0x00220000, 0x00000111,
        0x38400A03, 0x2401E0E0, 0x72A788D9, 0x88D9000E, 0x00004142, 0x43444546, 0x00000000,
        0x00000000, 0x00000000
};

#define NUM_WRITE_32 (sizeof(write_32BIT) / sizeof(write_32BIT[0]))

int write_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    int l_result;
    struct write_mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        printf("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    /* Perform 32-bit write operations */
    for (size_t i = 0; i < NUM_WRITE_32; i++) {
        s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
        s_obj_mem.address = write_32BIT[i];
        s_obj_mem.value = data_to_write_32BIT[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit write failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }

            DIR_LOG("INFO:\t Register: 0X%08X  Written Value: %08X\n", s_obj_mem.address, s_obj_mem.value);
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}

