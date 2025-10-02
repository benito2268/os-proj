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

Q :=@
ECHO_CC = @echo "  CC      $@"
ECHO_AS = @echo "  GAS     $@"
ECHO_LD = @echo "  LD      $@"

CFLAGS = -m32 -Wall -Wextra -std=gnu99 -ffreestanding -O0 -ggdb -nostdlib -I$(LIBPATH) \
         -fno-pic -fno-pie -fno-stack-protector -fno-strict-aliasing -fno-builtin -fno-omit-frame-pointer \
		 -Wno-unused-function -Wno-unused-variable -Wno-unused-parameter \

CPPFLAGS = 
LDFLAGS = -T../ldscript.ld -nostdlib -no-pie -L$(LIBPATH) -lgcc -lk
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
	$(Q)$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(ECHO_LD)
	$(Q)$(CC) -o $@ $^ $(LDFLAGS) 

clean:
	rm *.o		  || true
