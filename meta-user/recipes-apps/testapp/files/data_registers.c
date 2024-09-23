/****************************************************************************
 * @file:        data_registers.c
 * 
 * @Created:     06-08-2024
 *
 * @brief:       This file implements to read the status from the core and 
 * 		 also write into it.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "data_registers.h"

void list_categories(const char *filename, char categories[][MAX_LINE_LENGTH], int *category_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(DIR_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '=' && line[1] == '=') {
            // This is a category header
            sscanf(line, "== %[^\n] ==" , categories[count]);
            count++;
            if (count >= MAX_CATEGORIES) {
                break; // Avoid exceeding the array limit
            }
        }
    }

    fclose(file);
    *category_count = count;
}

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
int registerdata_main(void) {
    int l_hFile; /* File descriptor for the device driver */
    FILE *file;
    uint32_t l_result;
    char line[MAX_LINE_LENGTH];
    struct data_mem s_obj_mem;
    char selected_category[MAX_LINE_LENGTH];
    char categories[MAX_CATEGORIES][MAX_LINE_LENGTH];
    int category_count = 0;
    int in_selected_category = 0;

    // List categories from the file
    list_categories("data.txt", categories, &category_count);

    // Prompt the user to select a category
    printf("Available categories:\n");
    for (int i = 0; i < category_count; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }
    printf("Enter the number of the category you want to read: ");
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > category_count) {
        fprintf(stderr, "Invalid choice\n");
        return DIR_FAILURE;
    }
    getchar(); // Consume newline character left by scanf

    strcpy(selected_category, categories[choice - 1]);

    // Open the device driver path
    l_hFile = open(Driver_path, O_WRONLY);
    if (l_hFile == -1) {
        perror("open failed");
        return DIR_FAILURE;
    }
    printf("Opening %s\n", Driver_path);

    // Open the file
    file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        close(l_hFile);
        return DIR_FAILURE;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Check if the line is a category header
        if (line[0] == '=' && line[1] == '=') {
            if (in_selected_category) {
                in_selected_category = 0;
            }
            if (strstr(line, selected_category)) {
                in_selected_category = 1;
            }
            continue; // Skip header lines
        }

        // Process addresses only if in the selected category
        if (in_selected_category) {
            // Initialize the structure
            s_obj_mem.value = 0;  // Set value to 0 if not provided

            // Parse the line
            char opStr[10];
            int fields = sscanf(line, "%x %s", &s_obj_mem.address, opStr);

	    if (fields == 2) {
            s_obj_mem.value = 0;  // Make sure value is 0 if not provided
            if (strcmp(opStr, "read") == 0) {
                s_obj_mem.operation = 3;  // Operation code for read
            } else {
                printf("Unknown operation: %s\n", opStr);
                continue;
            }
        } else if (fields == 3) {
            if (strcmp(opStr, "read") == 0) {
                s_obj_mem.operation = 3;  // Operation code for read
            } else if (strcmp(opStr, "write") == 0) {
                s_obj_mem.operation = 6;  // Operation code for write
            } else {
                printf("Unknown operation: %s\n", opStr);
                continue;
            }
        } else {
            printf("Error parsing line: %s\n", line);
            continue;
        }

	    l_result = ioctl(l_hFile,0,&s_obj_mem);
	    if (s_obj_mem.operation == 3) {
            printf("INFO:\t Register: 0x%08X Value: 0x%08X\n", s_obj_mem.address, l_result);
        } else if (s_obj_mem.operation == 6) {
            printf("INFO:\t Register: 0x%08X Value: 0x%08X\n", s_obj_mem.address, s_obj_mem.value);
        }
      }
   }
    // Close the file and the device driver
    fclose(file);
    close(l_hFile);
    return DIR_SUCCESS;
}
