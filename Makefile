#compiler tools
TARGET = SweepOS.bin
ISO    = SweepOS.iso

CCDIR = ~/opt/cross/bin
LIBDIR = ~/opt/cross/lib/gcc/i386-elf/14.0.1

CC = $(CCDIR)/i386-elf-gcc
CPP = $(CCDIR)/i386-elf-g++
LD = $(CCDIR)/i386-elf-ld
AS = $(CCDIR)/i386-elf-as

CFLAGS = -m32 -Wall -Wextra -std=gnu99 -ffreestanding -O2 -g -nostdlib
CPPFLAGS = 
LDFLAGS = -Tldscript.ld -nostdlib -lgcc
ASFLAGS =

CFILES = $(wildcard *.c)
CPPFILES = $(wildcard *.cpp)
ASMFILES = $(wildcard *.S)

OBJS := $(CFILES:.c=.o) $(ASMFILES:.S=.o) $(CPPFILES:.cpp=.o)

all: $(ISO)

.PHONY: clean qemu-nox

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(ISO): $(TARGET)
	mkdir -p isodir/boot/grub
	cp $^ isodir/boot/$@
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

qemu-nox:
	qemu-system-i386 -nographic $(ISO)

clean:
	rm $(TARGET) || true
	rm $(ISO)	 || true
	rm *.o		 || true