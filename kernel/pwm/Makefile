PWD := $(shell pwd)
obj-m += pwm_main.o
KERNEL=~/felabs/sysdev/tinysystem/linux-2.6.34
CROSS=/usr/local/xtools/arm-unknown-linux-uclibcgnueabi/bin/arm-linux-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) SUBDIRS=$(PWD) modules

userSpace:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C $(KERNEL) SUBDIRS=$(PWD) clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
