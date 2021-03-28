# Makefile – makefile of our secend driver
#
# # if KERNELRELEASE is not defined, we've been called directly from the command line.
# # Invoke the kernel build system. 

obj-m += netfilter_hook.o    
CURRENT_PATH := $(shell pwd)  
LINUX_KERNEL := $(shell uname -r)  
LINUX_KERNEL_PATH := /lib/modules/$(shell uname -r)/build 
KBUILD_CFLAGS   += -g

all:
	make -k -C $(LINUX_KERNEL_PATH)  M=$(CURRENT_PATH) modules  
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean  

