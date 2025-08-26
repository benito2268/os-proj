# isr_asm.S - defines isr handlers 0-31
# Ben Staehle - 8/19/25

.code32
.section .text

.globl isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7
.globl isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15
.globl isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23
.globl isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31

.extern isr_handler

# macro to generate isrs with no error code
.macro ISR_NOERR num
	cli
	pushl $0
	pushl $\num
	jmp   isr_common_stub
.endm

# macro to generate isrs with an error code
.macro ISR_ERR num
	cli
	pushl $\num
	jmp   isr_common_stub
.endm

isr_common_stub:
