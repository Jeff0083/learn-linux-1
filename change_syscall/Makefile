# Makefile – makefile of our secend driver
#
# # if KERNELRELEASE is not defined, we've been called directly from the command line.
# # Invoke the kernel build system. 
#obj-m += zjp_ofcd_class.o        # 产生ofcd 模块的目标文件
obj-m += change_sys_call_table.o        # 产生ofcd 模块的目标文件
CURRENT_PATH := $(shell pwd)   #模块所在的当前路径
LINUX_KERNEL := $(shell uname -r)    #Linux内核源代码的当前版本
LINUX_KERNEL_PATH := /lib/modules/$(shell uname -r)/build  #Linux内核源代码的绝对路径
all:
	make -k -C $(LINUX_KERNEL_PATH)  M=$(CURRENT_PATH) modules   #编译模块了
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean    #清理

