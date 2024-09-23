APP = testapp

# Add any other object files to this list below
SRC = i2c.c ddr.c spi.c uart.c core_read.c core_write.c core_configuration_1GB.c ethernet.c registers.c can_registers.c AFDX_registers.c axi_registers.c core_configuration_100MB.c crc_core.c data_registers.c OAP_rw.c IAP_rw.c MDIO_write.c MDIO_read.c AFDX_port_status.c MDIO_clk.c AFDX_reset.c sample_crc.c write_sample.c testapp.c   
APP_OBJS = $(SRC:.c=.o)
#APP_OBJS = testapp.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) -o $@ $(APP_OBJS) $(LDFLAGS) $(LDLIBS)
clean:
	rm -f $(APP) *.o
