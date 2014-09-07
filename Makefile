#
# Makefile for /dev/string module
#

#
# Comment this line to turn off debugging output.
#
CFLAGS+=-DXLATE_DEBUG

KMOD=string_module
SRCS=string_module.c
SRCS+=device_if.h bus_if.h

.include <bsd.kmod.mk>
