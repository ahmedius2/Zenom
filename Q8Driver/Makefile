####################################################################
# MAKEFILE TEMPLATE FOR KERNEL MODULES AND USER SPACE APPLICATIONS #
########################### EK@GYTE ################################
####################################################################
KERNELMODULES     ?=  q8driver   
### SKIN = xeno, posix etc.
SKIN              ?= xeno
UNAME             := $(shell uname -r)
KERNELSOURCEDIR   ?= /lib/modules/$(UNAME)/build

### Xenomai directory, xeno-config and library directory ###########
XENO_DIR          ?= /usr/xenomai
XENO_CONFIG       ?= $(XENO_DIR)/bin/xeno-config
XENO_LIB_DIR      ?= $(shell $(XENO_CONFIG) --library-dir)

### General configuration stuff ####################################

CC                =  $(shell $(XENO_CONFIG) --cc)

################ KERNEL MODULE START ###############################
OBJS      := ${patsubst %, %.o, $(KERNELMODULES)}
CLEANTHIS := ${patsubst %, .%*, $(KERNELMODULES)}

#ifneq ($(KERNELMODULES),)
#ifeq ($(findstring 2.6,$(KERNELSOURCEDIR)),2.6)
### KERNEL 2.6 #####################################################

obj-m	       := $(OBJS)
EXTRA_CFLAGS := -I$(XENO_DIR)/include
PWD          := $(shell pwd)


all::
	$(MAKE) -C $(KERNELSOURCEDIR) SUBDIRS=$(PWD) modules	

driver:: 
	   $(MAKE) -C $(KERNELSOURCEDIR) SUBDIRS=$(PWD) modules
	
#endif
#endif

clean::
	$(RM) $(CLEANTHIS) *.cmd *.o *.ko *.mod.c
	$(RM) -R .tmp*
################ KERNEL MODULE END #################################


.PHONY: clean

