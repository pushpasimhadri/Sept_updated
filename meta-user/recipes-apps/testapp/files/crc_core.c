/****************************************************************************
 * @file:        crc_core.c
 * 
 * @Created:     18-07-2024
 *
 * @brief:       To file implements to calculate CRC for the Data and Block_Id,
 * 		 Block_length, Global.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "crc_core.h"

// Function to reflect bits
uint32_t reflect(uint32_t data, int bits) {
    uint32_t reflection = 0;
    for (int bit = 0; bit < bits; bit++) {
        if (data & 1) {
            reflection |= (1 << ((bits - 1) - bit));
        }
        data = (data >> 1);
    }
    return reflection;
}

// Function to calculate CRC
uint32_t calculate_crc(uint32_t *data, int length, uint32_t polynomial) {
    uint32_t crc = CRC_INIT;
    for (int j = 0; j < length; j++) {
        uint32_t block = reflect(data[j], 32);
        for (int i = 0; i < 32; i++) {
            uint32_t bit = (block >> (31 - i)) & 1;
            uint32_t c = (crc >> 31) & 1;
            crc <<= 1;
            if (c ^ bit) {
                crc ^= polynomial;
            }
        }
    }

    crc = reflect(crc, 32);
    return crc ^ 0xFFFFFFFF;
}

// Function to handle CRC calculation for Block ID and Block Length
int crc_block_id_length() {
    uint32_t block_id, block_length;

    // Get Block ID from the user
    DIR_LOG("Enter Block ID in hex format: ");
    if (scanf("%x", &block_id) != 1) {
        DIR_ERRLOG("Invalid input for Block ID\n");
        return DIR_FAILURE;
    }

    // Get Block Length from the user
    DIR_LOG("Enter Block Length in hex format: ");
    if (scanf("%x", &block_length) != 1) {
        DIR_ERRLOG("Invalid input for Block Length\n");
        return DIR_FAILURE;
    }

    // Calculate CRC for Block ID and Block Length
    uint32_t crc_id_length_data[2];
    crc_id_length_data[0] = block_id;
    crc_id_length_data[1] = block_length;
    uint32_t crc_id_length = calculate_crc(crc_id_length_data, 2, POLYNOMIAL);

    // Output CRC result
    DIR_LOG("CRC for Block ID and Block Length: %08X\n", crc_id_length);

    return DIR_SUCCESS;
}

// Function to handle CRC calculation for Data Blocks
int crc_data_blocks() {
    int num_data_blocks;

    // Get number of data blocks
    DIR_LOG("Enter number of data blocks: ");
    if (scanf("%d", &num_data_blocks) != 1) {
        DIR_ERRLOG("Invalid input for number of data blocks\n");
        return DIR_FAILURE;
    }

    uint32_t *data_blocks = (uint32_t *)malloc(num_data_blocks * sizeof(uint32_t));
    if (!data_blocks) {
        DIR_ERRLOG("Memory allocation failed\n");
        return DIR_FAILURE;
    }

    for (int i = 0; i < num_data_blocks; i++) {
        DIR_LOG("Enter data block %d in hex format: ", i + 1);
        if (scanf("%x", &data_blocks[i]) != 1) {
            DIR_ERRLOG("Invalid input for data block %d\n", i + 1);
            free(data_blocks);
            return DIR_FAILURE;
        }
    }

    // Calculate CRC for data blocks
    uint32_t crc_data = calculate_crc(data_blocks, num_data_blocks, POLYNOMIAL);
    free(data_blocks);

    // Output CRC result
    DIR_LOG("CRC for Data Blocks: %08X\n", crc_data);

    return DIR_SUCCESS;
}

// Function to calculate the Global CRC
int crc_global() {

    // Define hardcoded data blocks
    uint32_t data_blocks[NUM_DATA_BLOCKS] = {
        0x8B000987,0x00000000,0x00000001,0xDD9EB80C,0x81F20000,0x9D71EF95,0x04000000,0x00000001,
	0x281E1ECC,0x001F4000,0x9C845C42,0x07000000,0x00000003,0xC5B7AC97,0x00000000,0x00000001,
	0xE0000000,0x17752489,0x0A000000,0x00000011,0xC737F732,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10D76EAD,0x01000000,
	0x00000001,0xE0FE91BC,0x00000000,0x2144DF1C,0x02000000,0x00000002,0xB5EB4482,0x00000000,
	0x47D41000,0x74E8A831,0x03000000,0x00000001,0x9A3EC2DC,0x00020000,0x1372BD9E,0x05000000,
	0x00000003,0xBF77FFF7,0x00000000,0x00000000,0x00000000,0x7BD5C66F,0x06000000,0x00000001,
	0x52DE4DAC,0x7FF7FF00,0x049BF026,0x08000000,0x00000002,0xFF5B5C23,0x0A000000,0xE7F9FE00,
	0x6BD8B43D,0x09000000,0x00000001,0xD08EDA7D,0x10000000,0x3CF3CF78,0x0B000000,0x00000003,
	0x00474196,0xFE000000,0x06EAB6EA,0x00208400,0x3F73C7EE,0x20000000,0x00000003,0xB6565F83,
	0xBABE0000,0x5678BAAD,0x00000000,0xD3CF6092,0x21000000,0x00000003,0x8B367633,0x00000000,
	0x00000000,0x20040000,0x24D723A3,0x22000000,0x00000001,0x669FC468,0x00000000,0x2144DF1C,
	0x23000000,0x0000000E,0x039CFD8E,0x00000000,0x00500000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x4556DE60,0x24000000,0x00000001,0xE9DF31C8,0x00000000,0x2144DF1C,0x25000000,
	0x00000002,0xC60AB796,0x80000000,0x20500015,0x32D6B5CA,0x27000000,0x00000001,0xAE7F4B18,
	0x00000000,0x2144DF1C,0x29000000,0x00000003,0xBB463DF2,0x757C0000,0x3C03755B,0x0FF04010,
	0xDD4D34A5,0x00000000,0x00000000
    };

    // Calculate Global CRC
    uint32_t crc = calculate_crc(data_blocks, NUM_DATA_BLOCKS, POLYNOMIAL_GLOBAL);

    // Output CRC result
    DIR_LOG("Global CRC : %08X\n", crc);

    return DIR_SUCCESS;
}

/*Function name:
 *    crc_main - This function implements to calculate crc.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the CRC for the data and Block Id, Block length, and Global CRC are calculated successfully,function will return DIR_SUCCESS
 *      DIR_FAILURE - If the entered data is invalid, function will return DIR_FAILURE
 */
int crc_main() {
    int choice;
    int status;

    // Display menu
    DIR_LOG("Select an option:\n");
    DIR_LOG("1. Calculate CRC for Block ID and Block Length\n");
    DIR_LOG("2. Calculate CRC for Data Blocks\n");
    DIR_LOG("3. Calculate CRC for Global Data\n");
    DIR_LOG("Enter your choice (1, 2, 3): ");
    if (scanf("%d", &choice) != 1) {
        DIR_ERRLOG("Invalid input for choice\n");
        return -1;
    }

    switch (choice) {
        case 1:
            status = crc_block_id_length();
            break;
        case 2:
            status = crc_data_blocks();
            break;
	case 3:
            status = crc_global(); 
	    break;
        default:
            DIR_ERRLOG("Invalid choice\n");
            return DIR_FAILURE;
    }

    return status;
}
