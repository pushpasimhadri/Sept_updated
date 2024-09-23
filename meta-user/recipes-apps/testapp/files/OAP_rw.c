
#include "OAP_rw.h"

unsigned int address_BIT[] = {
    0x80040008, 0x80040000, 0x80040004, 0x80040008, 0x8004000c, 0x8004000c,
    0x80040010, 0x80040014, 0x80040018, 0x8004001c, 0x80040020, 0x80040024,
    0x80040028, 0x8004002c, 0x80040030, 0x80040034, 0x80040038, 0x8004003c,
    0x80040040, 0x80040044
};
unsigned int write_values[]= {
    0x003c0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x123456A0, 0x123456A1, 0x123456A2,
    0x123456A3, 0x123456A4, 0x123456A5, 0x123456A6, 0x123456A7, 0x123456A8,
    0x123456A9, 0x123456AA
};

#define OPRWB 0b00000000000000011110

int OAP_read_write_seq(void)
{
        int l_hFile;
        uint32_t l_result;
        struct mem_seq s_obj_mem;

        /* Open the device driver path */
        l_hFile = open(Driver_path, O_RDWR);

        /* Check if the device driver was opened successfully */
        if (l_hFile == -1) {
                DIR_ERRLOG("open failed for %s\n", Driver_path);
                return DIR_FAILURE;
        }

        DIR_LOG("Opened /dev/ModuleDiagnostic\n");


        for (size_t i = 0; i <= 19; i++) {

        if ( (OPRWB >> i) & 1){
                s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
                s_obj_mem.address = address_BIT[i];
                l_result = ioctl(l_hFile, 0, &s_obj_mem);

                if (l_result == -1) {
                        DIR_ERRLOG("32-bit read failed for address %X\n", s_obj_mem.address);
                        close(l_hFile);
                        return DIR_FAILURE;
                }
		DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, l_result);
        }
	//DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, l_result);
	else
		{
			s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
			s_obj_mem.address = address_BIT[i];
			s_obj_mem.value = write_values[i];
			l_result = ioctl(l_hFile, 0, &s_obj_mem);
			if (l_result == -1) {
				printf("32-bit write failed for address %X\n", s_obj_mem.address);
				close(l_hFile);
				return DIR_FAILURE;
				}
			DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, s_obj_mem.value);
			}

      //  DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, s_obj_mem.value);
	}

   /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
