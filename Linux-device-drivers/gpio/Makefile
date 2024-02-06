obj-m += gpio_sysfs.o
gpio_sysfs-objs += gpio.o gpio_syscalls.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
