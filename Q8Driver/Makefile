# Kernel module makefile

UNAME       := $(shell uname -r)
KERNELDIR   ?= /lib/modules/$(UNAME)/build
PWD     	:= $(shell pwd)

obj-m	+= q8driver.o

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules	

clean:
	$(RM) $(OBJS) *.cmd *.o *.ko *.mod.c Module.symvers modules.order
	$(RM) -R .tmp*
