# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
# This runs in the kernel build system.
ifneq ($(KERNELRELEASE),)
	obj-m := ex01_simple_module.o	
	obj-m += print_currect_process_module.o	
	obj-m += ex0203_simple_module.o
	ex0203_simple_module-objs := ex02_simple_module_init.o ex03_simple_module_exit.o 
	obj-m += ex04_simple_module__init_token.o

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
# This runs in the module directory.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
	
.PHONY: all clean

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif