#include "sample_crc.h"

// Reflects the bits of a data word (e.g., 32-bit)
uint32_t reflect_sample(uint32_t data, int bits) {
    uint32_t reflection = 0;
    for (int bit = 0; bit < bits; bit++) {
        if (data & 1) {
            reflection |= (1 << ((bits - 1) - bit));
        }
        data = (data >> 1);
    }
    return reflection;
}

// Function to calculate CRC using reflection
uint32_t calculate_crc_sample(uint32_t *data, int length, uint32_t polynomial) {
    uint32_t crc = CRC_INIT;
    for (int j = 0; j < length; j++) {
        uint32_t block = reflect_sample(data[j], 32);
        for (int i = 0; i < 32; i++) {
            uint32_t bit = (block >> (31 - i)) & 1;
            uint32_t c = (crc >> 31) & 1;
            crc <<= 1;
            if (c ^ bit) {
                crc ^= polynomial;
            }
        }
    }
    crc = reflect_sample(crc, 32);
    return crc ^ 0xFFFFFFFF;
}

// Function to write data to a file
void write_data_to_file(const char *filename, uint32_t *data, int length) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening value file for writing");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < length; i++) {
        fprintf(file, "%08X\n", data[i]);
    }
    fclose(file);
}

// Function to read data from a file and calculate its CRC
uint32_t calculate_crc_from_file(const char *filename, uint32_t polynomial) {
    FILE *file;
    uint32_t data;
    uint32_t crc = CRC_INIT;
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening value file for reading");
        exit(EXIT_FAILURE);
    }
    while (fscanf(file, "%08X", &data) != EOF) {
        data = reflect_sample(data, 32);
        for (int i = 0; i < 32; i++) {
            uint32_t bit = (data >> (31 - i)) & 1;
            uint32_t c = (crc >> 31) & 1;
            crc <<= 1;
            if (c ^ bit) {
                crc ^= polynomial;
            }
        }
    }
    fclose(file);
    crc = reflect_sample(crc, 32);
    return crc ^ 0xFFFFFFFF;
}

int sample_crc_main() {
    FILE *file;
    ssize_t read;
    size_t len = 0;
    char *line = NULL;
    unsigned int address, data, c = 0;  // 'c' stores the calculated CRC
    char operation[10], info[50];
    unsigned int data_store[1024];  // Array to store the data for CRC calculation
    int data_count = 0;  // Counter for the number of data items
    int crc_start = 0;   // Flag to indicate the start of CRC calculation
    const uint32_t polynomial = 0x04C11DB7;  // Standard CRC-32 polynomial for block-wise CRC
    const uint32_t koopman_polynomial = 0x20044009;  // Koopman CRC polynomial

    // Open the data file
    file = fopen("write_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Open value2.txt to write data for Koopman CRC calculation
    FILE *value_file = fopen(VALUE_FILE, "w");
    if (value_file == NULL) {
        perror("Error opening value file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read each line from the file
    while ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character

        // Parse the line in the format: address operation data info
        if (sscanf(line, " %x %s %x %[^\n]", &address, operation, &data, info) == 4) {

            // If the line contains "Device_id", just print it and write it to value2.txt
            if (strstr(info, "Device_id") != NULL) {
                printf("%08X %s %08X %s\n", address, operation, data, info);
                fprintf(value_file, "%08X\n", data);  // Write Device_id data to value2.txt
                continue;  // Skip this line from block-wise CRC calculation
            }

            // Write the data value to value2.txt for Koopman CRC
            fprintf(value_file, "%08X\n", data);

            // If the line contains "crc_std", calculate and print the block-wise CRC value
            if (strstr(info, "crc_std") != NULL) {
                c = calculate_crc_sample(data_store, data_count, polynomial);  // Calculate CRC
                printf("%08X w %08X crc (calculated): %08X\n", address, c, c);  // Print the calculated CRC
                data_count = 0;  // Reset data count for the next CRC block
            } else {
                // Print the normal operation line
                printf("%08X %s %08X %s\n", address, operation, data, info);

                // Start block-wise CRC calculation from "Schedule Table" onward
                if (!crc_start && strstr(info, "Schedule Table") != NULL) {
                    crc_start = 1;  // Enable CRC calculation
                }

                // Store data in the array for block-wise CRC calculation if crc_start is true
                if (crc_start) {
                    data_store[data_count++] = data;
                }
            }
        }
    }

    // Cleanup and close files
    fclose(file);
    fclose(value_file);
    if (line) {
        free(line);
    }

    // Calculate and print CRC for value2.txt with the Koopman polynomial
    uint32_t value_crc = calculate_crc_from_file(VALUE_FILE, koopman_polynomial);
    printf("CRC for %s: %08X\n", VALUE_FILE, value_crc);

    return 0;
}

