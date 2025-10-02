#compiler tools
TARGET = libk.a

CCDIR = /home/ben/opt/cross/bin
LIBDIR = /home/ben/opt/cross/lib/gcc/i686-elf/15.2.0

CC = $(CCDIR)/i686-elf-gcc
CPP = $(CCDIR)/i686-elf-g++
LD = $(CCDIR)/i686-elf-ld
AS = $(CCDIR)/i686-elf-as
AR = $(CCDIR)/i686-elf-ar

Q :=@
ECHO_CC = @echo "  CC      $@"
ECHO_AS = @echo "  GAS     $@"
ECHO_LD = @echo "  LD      $@"
ECHO_AR = @echo "  AR      $@"

CFLAGS = -m32 -Wall -Wextra -std=gnu99 -ffreestanding -O0 -g -nostdlib
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
	$(ECHO_CC)
	$(Q)$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(ECHO_AS)
	$(Q)$(AS) $(ASFLAGS) -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(ECHO_AR)
	$(Q)$(AR) rcs $@ $^ 

clean:
	rm $(TARGET) || true
	rm *.o		 || true
