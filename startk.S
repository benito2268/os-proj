.set ALIGN,         1 << 0
.set MEMINFO,       1 << 1
.set FLAGS,         ALIGN | MEMINFO
.set MAGIC,         0x1badb002
.set CHECKSUM,      -(MAGIC + FLAGS)
.set STACK_CANARY,  0x1badf00d

.section .multiboot

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

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
    call  kmain
    cli
    jmp .
