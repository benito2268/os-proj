# main Makefile - calls bash scripts to build kernel and libk
# Ben Staehle - 8/26/25

TARGET = os.elf
ISO = os.iso

BASH = bash
CD   = cd

GDB = ~/opt/cross/gdb/gdb 
GDBRC = ./start.gdb

all: build

.PHONY: build clean qemu kernel-as-lst

build:
	$(BASH) build_libk.sh
	$(BASH) build_kern.sh
	mkdir -p isodir/boot/grub
	cp $(TARGET) isodir/boot/$(ISO)
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir

qemu:
	qemu-system-i386 -vga std -display gtk,zoom-to-fit=on -cdrom $(ISO) -D qemu.log -d int

qemu-gdb:
	qemu-system-i386 -vga std -display gtk,zoom-to-fit=on -cdrom $(ISO) -D qemu.log -d int -s -S

gdb:
	$(GDB) -x $(GDBRC) -tui

clean:
	$(BASH) clean.sh
	rm $(TARGET) || true
	rm $(ISO)	 || true
	rm isodir/boot/os.iso || true 
	rm qemu.log
