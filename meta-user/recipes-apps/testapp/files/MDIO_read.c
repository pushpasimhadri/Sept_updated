#include "MDIO_read.h"

unsigned int address_MDIO[] = {
    0x80102000, 0x80102000, 0x80102000, 0x80102000, 0x80102000
};
unsigned int write_MDIO[]= {
    0x804D001F, 0x804E0086, 0x804D401F, 0x004E0000, 0x00000000
};

#define OPRWB 0b10000

int MDIO_delay_read(void)
{
        int l_hFile;
        uint32_t l_result;
        struct MR_mem_seq s_obj_mem;

        /* Open the device driver path */
        l_hFile = open(Driver_path, O_RDWR);

        /* Check if the device driver was opened successfully */
        if (l_hFile == -1) {
                DIR_ERRLOG("open failed for %s\n", Driver_path);
                return DIR_FAILURE;
        }

        DIR_LOG("Opened /dev/ModuleDiagnostic\n");


        for (size_t i = 0; i <= 4; i++) {

        if ( (OPRWB >> i) & 1){
                s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
                s_obj_mem.address = address_MDIO[i];
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
			s_obj_mem.address = address_MDIO[i];
			s_obj_mem.value = write_MDIO[i];
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
