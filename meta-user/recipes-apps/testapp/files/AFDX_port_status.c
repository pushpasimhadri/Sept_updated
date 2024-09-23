#include "AFDX_port_status.h"

unsigned int port_address[] = {
    0x80117400, 0x80117404, 0x80117408, 0x8011740C, 0x80117410, 0x80117414,
    0x80117418, 0x8011741C, 0x80117420, 0x80117424, 0x80117428, 0x8011742C,
    0x80117430, 0x80117440, 0x80117444, 0x80117448, 0x8011744C, 0x80117450,
    0x80117454, 0x80117458, 0x8011745C, 0x80117460, 0x80117464, 0x80117468,
    0x8011746C, 0x80117470, 0x80117004
};
unsigned int port_write_values[]= {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
};

#define OPRWB 0b111111111111111111111111111

int port_status(void)
{
        int l_hFile;
        uint32_t l_result;
        struct port_mem_seq s_obj_mem;

        /* Open the device driver path */
        l_hFile = open(Driver_path, O_RDWR);

        /* Check if the device driver was opened successfully */
        if (l_hFile == -1) {
                DIR_ERRLOG("open failed for %s\n", Driver_path);
                return DIR_FAILURE;
        }

        DIR_LOG("Opened /dev/ModuleDiagnostic\n");


        for (size_t i = 0; i <= 26; i++) {

        if ( (OPRWB >> i) & 1){
                s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
                s_obj_mem.address = port_address[i];
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
			s_obj_mem.address = port_address[i];
			s_obj_mem.value = port_write_values[i];
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

