#
# Makefile for /dev/xlate module
#

#
# Comment this line to turn off debugging output.
#
CFLAGS+=-DXLATE_DEBUG

KMOD=xlate_module
SRCS=xlate_module.c
SRCS+=device_if.h bus_if.h

.include <bsd.kmod.mk>
