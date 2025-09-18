# isr_asm.S - defines isr handlers 0-31
# Ben Staehle - 8/19/25

.code32
.section .text

.globl isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7
.globl isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15
.globl isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23
.globl isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31

.extern trap

# ISR with NO hardware error code
.macro ISR_NO_ERR num
    .globl isr\num
isr\num:
    cli
    pushl $0           # Push dummy error code
    pushl $\num        # Push trap number
    jmp isr_common_stub
.endm

# ISR WITH hardware-pushed error code
.macro ISR_ERR num
    .globl isr\num
isr\num:
    cli
    pushl $\num        # Push trap number ONLY
    jmp isr_common_stub
.endm

isr_common_stub:
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    pushal

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es

    call trap

    # errors never get here
    popal
    popl %gs
    popl %fs
    popl %es
    popl %ds

    addl $0x8, %esp
    iret

# isr definitions
ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR    8
ISR_NO_ERR 9
ISR_ERR    10
ISR_ERR    11
ISR_ERR    12
ISR_ERR    13
ISR_ERR    14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_ERR    17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31















