#compiler tools
TARGET = libk.a

CCDIR = /home/ben/opt/cross/bin
LIBDIR = /home/ben/opt/cross/lib/gcc/i686-elf/15.2.0

CC = $(CCDIR)/i686-elf-gcc
CPP = $(CCDIR)/i686-elf-g++
LD = $(CCDIR)/i686-elf-ld
AS = $(CCDIR)/i686-elf-as
AR = $(CCDIR)/i686-elf-ar

CFLAGS = -m32 -Wall -Wextra -std=gnu99 -ffreestanding -O2 -g -nostdlib
CPPFLAGS = 
LDFLAGS = -Tldscript.ld -nostdlib -lgcc
ASFLAGS =

CFILES = $(wildcard *.c)
CPPFILES = $(wildcard *.cpp)
ASMFILES = $(wildcard *.S)

OBJS     := $(CFILES:.c=.o) $(ASMFILES:.S=.o) $(CPPFILES:.cpp=.o)

all: $(TARGET)

.PHONY: clean

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^ 

clean:
	rm $(TARGET) || true
	rm *.o		 || true
