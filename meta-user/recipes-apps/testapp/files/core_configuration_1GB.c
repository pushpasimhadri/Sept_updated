/****************************************************************************
 * @file:        core_configuration_1GB.c
 * 
 * @Created:     22-08-2024
 *
 * @brief:       To configure the core using write operation.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "core_configuration_1GB.h"

unsigned int write_ope[] = {
    0x80116000, 0x80116004, 0x80116008, 0x8011600C, 0x80116010, 0x80116014, 0x80116018, 0x8011601C, 0x80116020,
    0x80116024, 0x80116028, 0x8011602C, 0x80116030, 0x80116034, 0x80116038, 0x8011603C, 0x80116040, 0x80116044,
    0x80116048, 0x8011604C, 0x80116050, 0x80116054, 0x80116058, 0x8011605C, 0x80116060, 0x80116064, 0x80116068,
    0x8011606C, 0x80116070, 0x80116074, 0x80116078, 0x8011607C, 0x80116080, 0x80116084, 0x80116088, 0x8011608C,
    0x80116090, 0x80116094, 0x80116098, 0x8011609C, 0x801160A0, 0x801160A4, 0x801160A8, 0x801160AC, 0x801160B0,
    0x801160B4, 0x801160B8, 0x801160BC, 0x801160C0, 0x801160C4, 0x801160C8, 0x801160CC, 0x801160D0, 0x801160D4,
    0x801160D8, 0x801160DC, 0x801160E0, 0x801160E4, 0x801160E8, 0x801160EC, 0x801160F0, 0x801160F4, 0x801160F8,
    0x801160FC, 0x80116100, 0x80116104, 0x80116108, 0x8011610C, 0x80116110, 0x80116114, 0x80116118, 0x8011611C,
    0x80116120, 0x80116124, 0x80116128, 0x8011612C, 0x80116130, 0x80116134, 0x80116138, 0x8011613C, 0x80116140,
    0x80116144, 0x80116148, 0x8011614C, 0x80116150, 0x80116154, 0x80116158, 0x8011615C, 0x80116160, 0x80116164,
    0x80116168, 0x8011616C, 0x80116170, 0x80116174, 0x80116178, 0x8011617C, 0x80116180, 0x80116184, 0x80116188,
    0x8011618C, 0x80116190, 0x80116194, 0x80116198, 0x8011619C, 0x801161A0, 0x801161A4, 0x801161A8, 0x801161AC,
    0x801161B0, 0x801161B4, 0x801161B8, 0x801161BC, 0x801161C0, 0x801161C4, 0x801161C8, 0x801161CC, 0x801161D0,
    0x801161D4, 0x801161D8, 0x801161DC, 0x801161E0, 0x801161E4, 0x801161E8, 0x801161EC, 0x801161F0, 0x801161F4,
    0x801161F8, 0x801161FC, 0x80116200, 0x80116204, 0x80116208, 0x8011620C, 0x80116210, 0x80116214, 0x80116218,
    0x8011621C, 0x80116220, 0x80116224, 0x80116228, 0x8011622C, 0x80116230, 0x80116234, 0x80116238, 0x8011623C,
    0x80116240, 0x80116244, 0x80116248, 0x8011624C, 0x80116250, 0x80116254, 0x80116258, 0x8011625C, 0x80116260,
    0x80116264, 0x80116268, 0x8011626C, 0x80116270, 0x80116274, 0x80116278, 0x8011627C, 0x80116280, 0x80116284,
    0x80116288, 0x8011628C, 0x80116290, 0x80116294, 0x80116298, 0x8011629C, 0x801162A0, 0x801162A4, 0x801162A8,
    0x801162AC, 0x801162B0, 0x801162B4, 0x801162B8, 0x801162BC, 0x801162C0, 0x801162C4, 0x801162C8, 0x801162CC,
    0x801162D0, 0x801162D4, 0x801162D8, 0x801162DC, 0x801162E0, 0x801162E4, 0x801162E8, 0x801162EC, 0x801162F0,
    0x801162F4, 0x801162F8, 0x801162FC, 0x80116300, 0x80116304
};

unsigned int write_data[] = {
	0x8B000987, 0x01000000, 0x00000002, 0xF24B3E52, 0x801FE000, 0x801FE000, 0xACE424BC, 0x02000000, 0x00000008,
	0xDA56A4E6, 0xC0000000, 0x8BD24C34, 0xC0000000, 0x8BD28C34, 0x00000000, 0x0BD44000, 0x00000000, 0x0BD48000,
	0x9CDB31E6, 0x03000000, 0x00000002, 0x888B6D32, 0x00010000, 0x00020000, 0x9C486E4E, 0x05000000, 0x00000003,
	0xBF77FFF7, 0x00000000, 0x00000000, 0x00000000, 0x7BD5C66F, 0x06000000, 0x00000002, 0x406BE242, 0x00778500,
	0x00707800, 0xDCF6675B, 0x08000000, 0x00000002, 0xFF5B5C23, 0x40000000, 0xA0000201, 0x503F97C3, 0x09000000,
	0x00000001, 0xD08EDA7D, 0xF80A0000, 0x68CD4DB8, 0x0B000000, 0x00000003, 0x00474196, 0x0E000000, 0x0C000000,
	0x607FF6F7, 0x390AD5E1, 0x20000000, 0x00000003, 0xB6565F83, 0x00000000, 0x00020300, 0x02000000, 0xE9FB1CD5,
	0x21000000, 0x0000000C, 0xD3556665, 0x00000000, 0x00000000, 0xE0100000, 0x00000000, 0x00000000, 0xE0180000,
	0x00000000, 0x00000000, 0xC0000000, 0x00000000, 0x00000000, 0xC0080000, 0x60CA0A0B, 0x22000000, 0x00000002,
	0x742A6B86, 0x0A000000, 0x0A000001, 0x77FB49B3, 0x23000000, 0x0000000E, 0x039CFD8E, 0x00000000, 0x002FFF04,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x003C0F0F, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x489248C0, 0x24000000, 0x00000002, 0xFB6A9E26, 0x00100000, 0x00120000,
	0x1E00AD21, 0x25000000, 0x00000014, 0xB378BFD5, 0x80000000, 0x01800015, 0xC0000000, 0x00000001, 0xC0000000,
	0x00000001, 0xC0000000, 0x00000001, 0xC0000000, 0x00000001, 0xC0000000, 0x00000001, 0xC0000000, 0x00000001,
	0xC0000000, 0x00000001, 0x40000000, 0x05000014, 0x40000000, 0x04800014, 0x41912565, 0x26000000, 0x00000020,
	0x8B91AAF3, 0x00092603, 0x8B000987, 0x00000001, 0x87654321, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x91885BE1, 0x27000000, 0x00000002,
	0xBCCAE4F6, 0x00058000, 0x00058000, 0x21BB4BED, 0x29000000, 0x0000000C, 0xE3252DA4, 0x00400000, 0xC0000000,
	0x0146EDC0, 0x00800000, 0xC0000000, 0x0146EDC0, 0x00000000, 0x78028000, 0x0142EE00, 0x00000000, 0x78028000,
	0x0142EE00, 0xD4C13D6E, 0x00000000, 0x00000000, 0x6F4D87A5
};

const char *header_names[] = {
	"Device_id", "Schedule Table", "BlockLength", "Local crc", "DATA", "Local crc", "Schedule Entry Points Table", "BlockLength","Local crc",
	"DATA", "Local crc", "Schedule Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc",
	"Clock Synchronization Parameter", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "[127:96]", "[159:128]", "[191:160]",
	"[223:192]", "[255:224]", "[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]",	"[479:448]", "[511:480]", "[543:512]",
	"Local crc", "IC/RM Table", "BlockLength", "Local crc", "DATA", "Local crc", "Output VL Table", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]",
	"crc_std", "Input VL Lookup Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Best-Effort Filter Table", "BlockLength", "Local crc",
	"DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Partition Space Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Shaping Parameters",
	"BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "Local crc", "IC/RM Parameters", "BlockLength", "Local crc", "DATA[31:0]", "Local crc",
	"General Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Output Parameters", "BlockLength", "Local crc",
	"DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "Output Port Table", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc",
	"Output Partition Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Input Parameters", "BlockLength", "Local crc", "DATA[31:0]", "[63:32]",
	"[95:64]", "[127:96]", "[159:128]", "[191:160]", "[223:192]", "[255:224]", "[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]",
	"crc_std", "Input Lookup Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Input Port Table", "BlockLength", "Local crc", "DATA[31:0]",
	"[63:32]", "Local crc", "Input Defragmentation Table", "BlockLength", "Local crc", "DATA[31:0]", "Local crc", "Output Sub-VL Table", "BlockLength",
	"crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "Local crc", "block id 0", "eof file(block length zero)", "koopman Global crc", "crc", "crc", "crc", "crc",
	"crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc",
	"crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc", "crc"
};

#define NUM_WRITE (sizeof(write_ope) / sizeof(write_ope[0]))

int core_conf_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    int l_result;
    struct conf_mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        printf("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    /* Perform 32-bit write operations */
    for (size_t i = 0; i < NUM_WRITE; i++) {
        s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
        s_obj_mem.address = write_ope[i];
        s_obj_mem.value = write_data[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit write failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }

    // Ensure i is within bounds of register_name array
        if (i < sizeof(header_names) / sizeof(header_names[0])) {
            DIR_LOG("INFO:\t %s\t Register: 0X%08X  Written Value: %08X\n", header_names[i], s_obj_mem.address, s_obj_mem.value);
        } else {
            DIR_LOG("INFO:\t Register: 0x%08X Value: %08X\n", s_obj_mem.address, l_result);
        }
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
