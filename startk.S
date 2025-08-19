# startk.S - specifies the multiboot header and starts the kernel
# Ben Staehle - 8/18/25

.set MAGIC,         0xE85250D6
.set ARCH_I386,     0x0
.set STACK_CANARY,  0x1BAD1BAD

.section .multiboot
.globl multiboot_header

.align 8

# --- multiboot2 header ---
multiboot_header:
.long MAGIC
.long ARCH_I386
.long header_end - multiboot_header
.long -(MAGIC + (header_end - multiboot_header))

# --- multiboot2 tags ---

.align 8
fb_tag:
.short 0x5                   # framebuffer request
.short 0x1
.long fb_tag_end - fb_tag    # size
.long 640                    # h-res
.long 480                    # v-res
.long 32                     # bits-per-pixel
fb_tag_end:

.align 8
end_tag:
.long 0
.long 8

header_end:

.section .bss

.align 16
stack_bot:
    .skip 0x4000
stack_top:

.section .text
.globl _start
.type _start, @function

.code32

_start:
    leal  stack_top, %esp
    movl  $STACK_CANARY, %esi
    pushl %esi
    movl  %esp, %ebp

    pushl %ebx
    call  kmain
    cli
spin:
    jmp spin
