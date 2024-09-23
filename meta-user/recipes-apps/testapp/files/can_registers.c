#include "can_registers.h"
/*
struct registers_mem {
    uint32_t address;
    uint32_t value;
    int operation;
};
*/
// Function prototypes
int write_registers(struct registers_mem *obj_mem, int hFile);
int read_registers(struct registers_mem *obj_mem, int hFile);
void delay_1ms(void);

int can_main() {
    int hFile;
    int status;
    struct registers_mem obj_mem[NUM_REGISTERS];

    // Open the device file
    hFile = open(Driver_path, O_RDWR);
    if (hFile < 0) {
        perror("Failed to open device file");
        return DIR_FAILURE;
    }

    // Define the sequence of operations
    int operations[] = {
        OP_32BIT_WRITE, OP_32BIT_WRITE, OP_32BIT_WRITE, OP_32BIT_WRITE, OP_32BIT_WRITE,
        OP_32BIT_WRITE, OP_32BIT_WRITE, OP_32BIT_WRITE, OP_32BIT_WRITE,
        OP_32BIT_READ, OP_32BIT_READ, OP_32BIT_READ, OP_32BIT_READ,
        OP_32BIT_WRITE, OP_32BIT_READ, OP_32BIT_WRITE, OP_32BIT_READ,
        OP_32BIT_READ, OP_32BIT_READ, OP_32BIT_READ, OP_32BIT_READ,
        OP_32BIT_READ, OP_32BIT_READ, OP_32BIT_READ
    };
    int num_operations = sizeof(operations) / sizeof(operations[0]);

    // Iterate through the array and perform the operations
    for (int i = 0; i < num_operations; i++) {
        if (operations[i] == OP_32BIT_WRITE) {
            status = write_registers(obj_mem, hFile);
            if (status != DIR_SUCCESS) {
                printf("Failed to write data during operation %d\n", i + 1);
                close(hFile);
                return DIR_FAILURE;
            }
        } else if (operations[i] == OP_32BIT_READ) {
            status = read_registers(obj_mem, hFile);
            if (status != DIR_SUCCESS) {
                printf("Failed to read data during operation %d\n", i + 1);
                close(hFile);
                return DIR_FAILURE;
            }
        }
    }

    // Close the device file
    close(hFile);

    return DIR_SUCCESS;
}

// Example write_registers function
int write_registers(struct registers_mem *obj_mem, int hFile) {
    uint32_t write_op[NUM_REGISTERS] = {0x80000200, 0x80002000, 0x80002700};
    uint32_t data_to_write[NUM_REGISTERS] = {0x11111111, 0x00000000, 0x12345678};

    for (int i = 0; i < NUM_REGISTERS; i++) {
        obj_mem[i].address = write_op[i];
        obj_mem[i].value = data_to_write[i];
        int l_result = ioctl(hFile, 0, &obj_mem[i]);
        if (l_result == -1) {
            perror("Failed to write the data");
            return DIR_FAILURE;
        }
        printf("INFO:\t Register: %X Value written: %X\n", obj_mem[i].address, obj_mem[i].value);
    }
    return DIR_SUCCESS;
}

// Example read_registers function
int read_registers(struct registers_mem *obj_mem, int hFile) {
    uint32_t read_operation[NUM_REGISTERS] = {0x80000204, 0x80000208, 0x80000210};

    for (int i = 0; i < NUM_REGISTERS; i++) {
        obj_mem[i].address = read_operation[i];
        int l_result = ioctl(hFile, 0, &obj_mem[i]);
        if (l_result == -1) {
            perror("Failed to read the registers");
            return DIR_FAILURE;
        }
        printf("INFO:\t Register: %X Value read: %X\n", obj_mem[i].address, l_result);
    }
    return DIR_SUCCESS;
}

// Delay function
void delay_1ms(void) {
    usleep(1000); // Sleep for 1000 microseconds (1 millisecond)
}
