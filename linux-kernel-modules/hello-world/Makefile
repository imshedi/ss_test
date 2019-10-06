obj-m := hello.o

all:
#	kedr start hello.ko -f leak_check.conf
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	dmesg -C
	insmod hello.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	dmesg -C
	rmmod hello
#	kedr stop
