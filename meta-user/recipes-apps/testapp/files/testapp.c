/**********************************************************************************************************
 *@file:         testapp.c
 *
 *@Created:      17-04-2024       
 *
 *@brief:        Menu driven program to implement testing of interfaces and accessing the registers.
 *
 *Description:   This file contains functions to test interfaces including I2C,DDR4,Ethernet and 
 		 access the registers to read and write.
 *
 *@version:      1.0
 *
 *@Author:       Capgemini Engineering
 ***********************************************************************************************************/

#include "testapp.h"

#define MAX_INPUT_LENGTH 2

char ip_address[MAX_IP_LENGTH];

int main() {
	int hFile;
	int l_result;
	char input[MAX_INPUT_LENGTH];

	while (1) {
		/* Display main menu options */
		printf("*****Entering into Options*****\n");
		printf("1. SDF FPGA PS\n");
		printf("2. SDF FPGA PL\n");
		printf("3. DMB FPGA PS\n");
		printf("4. DAB FPGA PS\n");
		printf("5. DAB FPGA PL\n");
		printf("6. FPGA read/write\n");
		printf("7. CAN Registers\n");
		printf("8. AFDX_Read\n");
		printf("9. core_configuration_100MB\n");
		printf("10. crc_core\n");
		printf("11. Read&Write operations\n");
		printf("12. core_read_Registers\n");
		printf("13. core_write_Registers\n");
		printf("14. core_configuration_1GB\n");
		printf("15. AXI_Registers\n");
		printf("16. OAP_rw Registers\n");
		printf("17. IAP_rw_Registers\n");
		printf("18. MDIO_read\n");
		printf("19. MDIO_write\n");
		printf("20. AFDX_port_status\n");
		printf("21. MDIO_clk\n");
		printf("22. AFDX_RESET\n");
		printf("23. sample_core_configuration\n");
		printf("24. sample_write\n");
		printf("25. QUIT\n");
		printf("Enter the option(1-25):\n");
		scanf("%d", &Menu);

		switch(Menu) {

			case 1:
				/* Display sub-options for SDF FPGA PS */
				printf("Entering into SDF FPGA PS sub_options\n");
				printf("1. UART\n");
				printf("2. QSPI\n");
				printf("3. DDR4\n");
				printf("4. I2C\n");
				printf("5. Ethernet_loopback\n");
				printf("6. Quit\n");
				printf("Enter the choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						/* Handle UART loopback test */
						l_result = uart_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("UART loopback Interface tested successfully.\n");
						else
							DIR_ERRLOG("Failed to test loopback for UART interface. Return error code: %d\n",l_result);
						break;

					case QSPI_Interface_test:
						/* Handle QSPI interface test */
						DIR_LOG("Boot Mode: QSPI 32 bit Boot Mode\n");
						DIR_LOG("Tested QSPI Interface successfully\n");
						break;

					case DDR4_Interface_test:
						DIR_LOG("DDR Interface test started\n");
						/* Handle DDR4 interface test */
						l_result = ddr_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("DDR memory test success\n");
						else
							DIR_ERRLOG("DDR memory test failed\n");
						break;

					case I2C_Interface_test:
						/* Handle I2C interface test */
						l_result = i2c_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("Read the data from EEPROM successfully.\n");
						else
							DIR_ERRLOG("Failed to read the data from the EEPROM. Return error code: %d\n", l_result);
						break;

					case Ethernet_loopback:
						/* Handle ethernet interface test */
						printf("Enter the IP address(self_ping or External_ping) format[xxx.xxx.xxx.xxx]:\n");
						scanf("%s", ip_address);
						struct sockaddr_in stSocadd;
						if(inet_pton(AF_INET, ip_address, &stSocadd.sin_addr) == 1)
							{
								l_result = ethernet_main(ip_address);
								if (l_result == PING_SUCCESS)
									DIR_LOG("GEM loopback Interface tested successfully.\n");
								else
									DIR_ERRLOG("Failed to test loopback for GEM Interface. Return error code: %d\n", l_result);
								}
						else
							{
								DIR_ERRLOG("Invalid IP address format");
								}
						break;

					case Quit:
						/* Exit the program */
						DIR_LOG("Exiting...\n");
						exit(0);
						break;

					default:
						/* Display Invalid choice message */
						DIR_ERRLOG("Invalid choice\n");
						break;
						}
					break;


			case 2:
				printf("Entering into SDF FPGA PL sub_options\n");
				printf("A. AFDX IP CORE\n");
				printf("B. Quit\n");
				printf("Enter your choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case AFDX_IP_CORE_test:
						l_result == registers_main();
						/* Handle read/write registers */
						if(l_result == DIR_SUCCESS)
							DIR_LOG("Read/Write operation successful\n");
						else
							DIR_ERRLOG("Failed to open the device path\n");
						break;

					case Quit:
						DIR_LOG("Exiting...\n");
						exit(0);
						break;

					default:
						DIR_ERRLOG("Invalid choice\n");
						break;
						}
					
					break;

			case 3:
				printf("Entering into the DMB FPGA PS sub_options\n");
				printf("1. UART\n");
				printf("2. QSPI\n");
				printf("3. DDR4\n");
				printf("4. I2C\n");
				printf("5. Ethernet_loopback\n");
				printf("6. Quit\n");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						/* Handle UART loopback test */
						l_result = uart_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("UART loopback Interface tested successfully.\n");
						else
							DIR_ERRLOG("Failed to test loopback for UART interface. Return error code: %d\n",l_result);
						break;

					case QSPI_Interface_test:
						DIR_LOG("Boot Mode: QSPI 32 bit Boot Mode\n");
						DIR_LOG("Tested QSPI Interface successfully\n");
						break;

					case DDR4_Interface_test:
						DIR_LOG("DDR Interface test started\n");
						/* Handle DDR4 interface test */
						l_result = ddr_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("DDR memory test success\n");
						else
							DIR_ERRLOG("DDR memory test failed\n");
						break;

					case I2C_Interface_test:
						/* Handle I2C interface test */
						l_result = i2c_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("Read the data from EEPROM successfully.\n");
						else
							DIR_ERRLOG("Failed to read the data from the EEPROM. Return error code: %d\n", l_result);
						break;

					case Ethernet_loopback:
						/* Handle ethernet interface test */
						DIR_LOG("Enter the IP address(self_ping or External_ping) format[xxx.xxx.xxx.xxx]:\n");
						scanf("%s", ip_address);
						struct sockaddr_in stSocadd;
						if(inet_pton(AF_INET, ip_address, &stSocadd.sin_addr) == 1)
							{
								l_result = ethernet_main(ip_address);
								if (l_result == PING_SUCCESS)
									DIR_LOG("GEM loopback Interface tested successfully.\n");
								else
									DIR_ERRLOG("Failed to test loopback for GEM Interface. Return error code: %d\n", l_result);
								}
						else
							{
								DIR_ERRLOG("Invalid IP address format");
								}
						break;

					case Quit:
						DIR_LOG("Exiting...\n");
						exit(0);
						break;

					default:
						DIR_ERRLOG("Invalid choice\n");
						break;
						}
					break;


			case 4:
				printf("Entering into the DAB FPGA PS sub_options\n");
				printf("1. UART\n");
				printf("2. QSPI\n");
				printf("3. DDR4\n");
				printf("4. I2C\n");
				printf("5. Ethernet_loopback\n");
				printf("6. Quit");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						/* Handle UART loopback test */
						l_result = uart_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("UART loopback Interface tested successfully.\n");
						else
							DIR_ERRLOG("Failed to test loopback for UART interface. Return error code: %d\n",l_result);
						break;

					case QSPI_Interface_test:
						DIR_LOG("Boot Mode: QSPI 32 bit Boot Mode\n");
						DIR_LOG("Tested QSPI Interface successfully\n");
						break;

					case DDR4_Interface_test:
						DIR_LOG("DDR Interface test started\n");
						/* Handle DDR4 interface test */
						l_result = ddr_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("DDR memory test success\n");
						else
							DIR_ERRLOG("DDR memory test failed\n");
						break;

					case I2C_Interface_test:
						/* Handle I2C interface test */
						l_result = i2c_main();
						if(l_result == DIR_SUCCESS)
							DIR_LOG("Read the data from EEPROM successfully.\n");
						else
							DIR_ERRLOG("Failed to read the data from the EEPROM. Return error code: %d\n", l_result);
						break;

					case Ethernet_loopback:
						/* Handle ethernet interface test */
						DIR_LOG("Enter the IP address(self_ping or External_ping) format[xxx.xxx.xxx.xxx]:\n");
						scanf("%s", ip_address);
						struct sockaddr_in stSocadd;
						if(inet_pton(AF_INET, ip_address, &stSocadd.sin_addr) == 1)
							{
								l_result = ethernet_main(ip_address);
								if (l_result == PING_SUCCESS)
									DIR_LOG("GEM loopback Interface tested successfully.\n");
								else
									DIR_ERRLOG("Failed to test loopback for GEM Interface. Return error code: %d\n", l_result);
								}
						else
							{
								DIR_ERRLOG("Invalid IP address format");
								}
						break;

					case Quit:
						DIR_LOG("Exiting...\n");
						exit(0);
						break;

					default:
						DIR_ERRLOG("Invalid choice\n");
						break;
						}
					break;

			case 5:
				printf("Entering into the DAB FPGA PL sub_options\n");
				printf("1. MES IP CORE\n");
				printf("2. Quit\n");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case MES_IP_CORE_test:
						l_result = registers_main();
						/* Handle read/write registers */
						if(l_result == DIR_SUCCESS)
							DIR_LOG("Read/Write operation successful\n");
						else
							DIR_ERRLOG("Failed to open the device path\n");
						break;

					case Quit:
						DIR_LOG("Exiting...\n");
						exit(0);
						break;
						}
					break;

			case 6:
				DIR_LOG("Entering into the Read/Write Registers\n");
				l_result = registers_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("Read/Write operation successful\n");
				else
					DIR_ERRLOG("Failed to perform Read/Write operation\n");
				break;

			case 7:
				DIR_LOG("Entering into the CAN Registers\n");
				l_result = can_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("Read/Write operation successful\n");
				else
					DIR_ERRLOG("Failed to perform Read/Write operation\n");
				break;

			case 8:
				DIR_LOG("Entering into the Read Only Registers\n");
				DIR_LOG("----------ES IP Interface map Unit--------------\n");
				l_result = AFDX_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("32-bit Read operation successful\n");
				else
					DIR_ERRLOG("Failed to perform 32-bit Read operation\n");
				break;

			case 9:
				l_result = core_configuration_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("core configuration successful\n");
				else
					DIR_ERRLOG("Failed to configure the core\n");
				break;

			case 10:
				l_result = crc_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("CRC for Block_id, Block_length and data calculated successfully\n");
				else
					DIR_ERRLOG("Failed to calculate CRC\n");
				break;

			case 11:
				l_result = registerdata_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("Read and write operations performed successfully\n");
				else
					DIR_ERRLOG("Failed to perform Read and Write operations\n");
				break;

			case 12:
				l_result = read_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("Read operation performed successfully\n");
				else
					DIR_ERRLOG("Failed to perform Read operations\n");
				break;

			case 13:
				l_result = write_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("Write operation performed successfully\n");
				else
					DIR_ERRLOG("Failed to perform Write operations\n");
				break;

			case 14:
				l_result = core_conf_main();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("core configuration successful\n");
                                else
                                        DIR_ERRLOG("Failed to configure the core\n");
                                break;

			case 15:
				l_result = axi_main();
				if(l_result == DIR_SUCCESS)
					DIR_LOG("AXI_LBC tested successfully\n");
				else
					DIR_ERRLOG("Failed to test AXI_LBC\n");
				break;

			case 16:
                                l_result = OAP_read_write_seq();
                                if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 17:
				l_result = IAP_read_write_seq();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 18:
				l_result = MDIO_delay_read();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 19:
				l_result = MDIO_delay_write();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 20:
				l_result = port_status();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 21:
				l_result = mdio_clk();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 22:
				l_result = AFDX_RESET();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write and read operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write and read operations\n");
                                break;

			case 23:
				l_result = sample_crc_main();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("core configuration successful\n");
                                else
                                        DIR_ERRLOG("Failed to configure the core\n");
                                break;

			case 24:
				l_result = write_sample_main();
				if(l_result == DIR_SUCCESS)
                                        DIR_LOG("Write operation performed successfully\n");
                                else
                                        DIR_ERRLOG("Failed to perform Write operations\n");
                                break;

			case 25:
				/* Exit the program */
				DIR_LOG("Exit\n");
				close(hFile);
				exit(0);
				break;
				}
		}
	return 0;
}