# kernel Makefile
# Ben Staehle - 8/26/25

TARGET = ../os.bin

CCDIR = /home/ben/opt/cross/bin
LIBDIR = /home/ben/opt/cross/lib/gcc/i686-elf/15.2.0

# can always assume libk exists, main makefile will build
LIBPATH = ../libc/
LIBK    = $(LIBPATH)/libk.a

CC = $(CCDIR)/i686-elf-gcc
CPP = $(CCDIR)/i686-elf-g++
LD = $(CCDIR)/i686-elf-ld
AS = $(CCDIR)/i686-elf-as

CFLAGS = -m32 -Wall -Wextra -std=gnu99 -ffreestanding -O0 -g -nostdlib -I$(LIBPATH)
CPPFLAGS = 
LDFLAGS = -T../ldscript.ld -nostdlib -L$(LIBPATH) -lgcc -lk
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
	$(CC) -o $@ $^ $(LDFLAGS) 

clean:
	rm *.o		  || true