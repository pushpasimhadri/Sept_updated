#
# This file is the testapp recipe.
#

SUMMARY = "Simple testapp application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "dpkg"
SRC_URI = "file://testapp.c \
	   file://ddr.c \
	   file://ddr.h \
	   file://testapp.h \
	   file://i2c.c \
	   file://i2c.h \
	   file://spi.h \
	   file://spi.c \
	   file://uart.h \
	   file://uart.c \
	   file://ethernet.c \
	   file://ethernet.h \
	   file://registers.h \
	   file://registers.c \
	   file://AFDX_registers.c \
	   file://AFDX_registers.h \
	   file://core_configuration_100MB.h \
	   file://core_configuration_100MB.c \
	   file://crc_core.h \
	   file://crc_core.c \
	   file://can_registers.c \
	   file://can_registers.h \
	   file://core_read.h \
	   file://core_read.c \
	   file://core_write.h \
	   file://core_write.c \
	   file://core_configuration_1GB.h \
	   file://core_configuration_1GB.c \
	   file://data_registers.h \
	   file://data_registers.c \
	   file://axi_registers.h \
	   file://axi_registers.c \
	   file://OAP_rw.h \
	   file://OAP_rw.c \
	   file://IAP_rw.h \
	   file://IAP_rw.c \
	   file://MDIO_write.h \
	   file://MDIO_write.c \
	   file://MDIO_read.h \
	   file://MDIO_read.c \
	   file://AFDX_port_status.h \
	   file://AFDX_port_status.c \
	   file://MDIO_clk.h \
	   file://MDIO_clk.c \
	   file://AFDX_reset.h \
	   file://AFDX_reset.c \
	   file://sample_crc.h \
	   file://sample_crc.c \
	   file://write_sample.h \
	   file://write_sample.c \
	   file://Makefile \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 testapp ${D}${bindir}
}

