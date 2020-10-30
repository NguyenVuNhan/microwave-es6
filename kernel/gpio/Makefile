obj-m += microwave.o
microwave-objs := 	main.o                              \
                    displayHandler/displayHandler.o     \
                    gpio/gpio_driver.o 		            \
                    gpio/include/common.o 	            \
                    init/startup.o                      \


PWD := $(shell pwd)
KERNEL=~/felabs/sysdev/tinysystem/linux-2.6.34
CROSS=/usr/local/xtools/arm-unknown-linux-uclibcgnueabi/bin/arm-linux-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) SUBDIRS=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	make -C $(KERNEL) SUBDIRS=$(PWD) clean


