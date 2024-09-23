#include "IAP_rw.h"

unsigned int address_32BIT[] = {
    0x800C0000, 0x800C0000, 0x800C0004, 0x800C0008, 0x800C000C, 0x800C0010,
    0x800C0014, 0x800C0018, 0x800C001C, 0x800C0020, 0x800C0024, 0x800C0028,
    0x800C002C, 0x800C0030, 0x800C0034, 0x800C0038, 0x800C003C, 0x800C0040, 
    0x800C0044, 0x800C0048, 0x800C0000, 0x800C0000
};
unsigned int write_values_32BIT[]= {
    0x20000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x80000000, 0x40000000
};

#define OPRWB 0b0011111111111111111110

int IAP_read_write_seq(void)
{
        int l_hFile;
        uint32_t l_result;
        struct IAP_mem_seq s_obj_mem;

        /* Open the device driver path */
        l_hFile = open(Driver_path, O_RDWR);

        /* Check if the device driver was opened successfully */
        if (l_hFile == -1) {
                DIR_ERRLOG("open failed for %s\n", Driver_path);
                return DIR_FAILURE;
        }

        DIR_LOG("Opened /dev/ModuleDiagnostic\n");


        for (size_t i = 0; i <= 21; i++) {

        if ( (OPRWB >> i) & 1){
                s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
                s_obj_mem.address = address_32BIT[i];
                l_result = ioctl(l_hFile, 0, &s_obj_mem);

                if (l_result == -1) {
                        DIR_ERRLOG("32-bit read failed for address %X\n", s_obj_mem.address);
                        close(l_hFile);
                        return DIR_FAILURE;
                }
		DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, l_result);
        }
	else
		{
			s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
			s_obj_mem.address = address_32BIT[i];
			s_obj_mem.value = write_values_32BIT[i];
			l_result = ioctl(l_hFile, 0, &s_obj_mem);
			if (l_result == -1) {
				printf("32-bit write failed for address %X\n", s_obj_mem.address);
				close(l_hFile);
				return DIR_FAILURE;
				}
			DIR_LOG("INFO:\t Register: 0X%08X  Value: %08X\n", s_obj_mem.address, s_obj_mem.value);
			}
	}

   /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}

