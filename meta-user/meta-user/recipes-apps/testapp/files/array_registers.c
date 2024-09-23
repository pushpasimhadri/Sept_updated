/*****************************************************************************
 * @file:       array_registers.c
 *
 * @Created:    03-06-2024
 *
 * @brief       This file implemented to read and write 8,16,32 bit registers
 *
 * @Version:    1.0
 *
 * @Author      Capgemini Engineering
 ******************************************************************************/

#include "array_registers.h"

// Array to hold the register values
volatile uint32_t registers[NUM_REGISTERS];

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
int access_registers_main() {
    int hFile;
    int status;
    struct registers_mem obj_mem[NUM_REGISTERS];

    // Open the device file
    hFile = open("/dev/Modulediagnostic", O_RDWR);
    if (hFile < 0) {
        perror("Failed to open device file");
        return DIR_FAILURE;
    }

    // Perform write operation
    status = write_registers(&obj_mem, hFile);
    if (status == DIR_SUCCESS) {
        printf("Data written successfully\n");
    } else {
        printf("Failed to write the data\n");
    }

    delay_1ms();

    // Perform read operation
    status = read_registers(&obj_mem, hFile);
    if (status == DIR_SUCCESS) {
        printf("Read the registers successfully\n");
    } else {
        printf("Failed to read the registers\n");
    }

    // Close the device file
    close(hFile);

    return 0;
}

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
int write_registers(struct registers_mem *obj_mem, int hFile) {
    uint32_t write_operation[NUM_REGISTERS] = {0x80000200, 0x80002000, 0x80002700};
    uint32_t data_to_write[NUM_REGISTERS] = {0x11111111, 0x00000000, 0x12345678};

    for (int i = 0; i < NUM_REGISTERS; i++) {
        obj_mem[i].address = write_operation[i];
        obj_mem[i].value = data_to_write[i];
        int result = ioctl(hFile, 0, &obj_mem[i]);
        if (result == -1) {
            perror("Failed to write the data");
            return DIR_FAILURE;
        }
        printf("INFO:\t Register: %X Value written: %X\n", obj_mem[i].address, obj_mem[i].value);
    }
    return DIR_SUCCESS;
}

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
int read_registers(struct registers_mem *obj_mem, int hFile) {
    uint32_t read_operation[NUM_REGISTERS] = {0x80000204, 0x80000208, 0x80000210};

    for (int i = 0; i < NUM_REGISTERS; i++) {
        obj_mem[i].address = read_operation[i];
        int result = ioctl(hFile, 0, &obj_mem[i]);
        if (result == -1) {
            perror("Failed to read the registers");
            return DIR_FAILURE;
        }
        printf("INFO:\t Register: %X Value read: %X\n", obj_mem[i].address, obj_mem[i].value);
    }
    return DIR_SUCCESS;
}

void delay_1ms(void) {
    usleep(1000); // Sleep for 1000 microseconds (1 millisecond)
}
