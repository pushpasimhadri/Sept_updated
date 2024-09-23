#include "data_registers.h"

/* Function to process operations from file */
int registerdata_main(void) {
    FILE *file;
    int l_hFile; /* File descriptor for the device driver */
    uint32_t l_result;
    struct mem s_obj_mem; /* Structure to store memory operation details */
    char line[256];
    char op[8];

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);
    if (l_hFile == -1) {
        DIR_ERRLOG("open failed for %s\n", Driver_path);
        return;
    }

    /* Open the input file */
    file = fopen("data.txt", "r");
    if (file == NULL) {
        DIR_ERRLOG("Error opening file data.txt\n");
        close(l_hFile);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        /* Parse each line */
        if (sscanf(line, "%x %s %x", &s_obj_mem.address, op, &s_obj_mem.value) == 3) {
            if (strcmp(op, "read") == 0) {
                s_obj_mem.operation = 3; /* 32-bit read */
            } else if (strcmp(op, "write") == 0) {
                s_obj_mem.operation = 6; /* 32-bit write */
            } else {
                DIR_ERRLOG("Unknown operation %s\n", op);
                continue;
            }

            l_result = ioctl(l_hFile, 0, &s_obj_mem);
            if (s_obj_mem.operation == 3) {
                DIR_LOG("INFO:\t Register: %08X Value: %08X\n", s_obj_mem.address, l_result);
            }
	    else if (s_obj_mem.operation == 6) {
		    DIR_LOG("INFO:\t Register: %08X Value: %08X\n", s_obj_mem.address, s_obj_mem.value);
            }

        } else {
            DIR_ERRLOG("Error parsing line: %s\n", line);
        }
    }

    /* Close the file and the device driver */
    fclose(file);
    close(l_hFile);
    return DIR_SUCCESS;
}
