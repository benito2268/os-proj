#!/bin/bash

qemu-system-i386 -vga std -display gtk,zoom-to-fit=on -cdrom "os.iso" -d int -s -S