#include "write_sample.h"

int write_sample_main() {
    FILE *file;
    char line[256];
    struct write_sample_mem mem_op;
    int fd, result;
    char operation[16]; // To store the operation type
    char filename[256]; // To store the file name

    // Prompt the user for the filename
    printf("Enter the name of the file to read data from: ");
    scanf("%s", filename);

    // Open the device driver
    fd = open(Driver_path, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    // Open the user-specified file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        close(fd);
        return DIR_FAILURE;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        unsigned int address, value;

        // Parse the line for address, operation, and value
        if (sscanf(line, "%x %s %x", &address, operation, &value) != 3) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            continue; // Skip invalid lines
        }

        // Only perform write operations
        if (strcmp(operation, "write") == 0) {
            mem_op.operation = OP_32BIT_WRITE;
            mem_op.address = address;
            mem_op.value = value;

            // Perform the write operation using ioctl
            result = ioctl(fd, 0, &mem_op);
            if (result == -1) {
                perror("ioctl failed");
                fclose(file);
                close(fd);
                return DIR_FAILURE;
            }
            printf("INFO:\t Register: 0X%08X  Written Value: %08X\n", mem_op.address, mem_op.value);
        }
    }

    // Close the file and device
    fclose(file);
    close(fd);
    return DIR_SUCCESS;
}
