# mmu_asm.S - assmebly code for configuring the MMU
# Ben Staehle - 9/4/25
.code32

.section .data

.ljmp_addr:
    .long 0
    .word 0
    
.section .text

.globl set_gdt
.type set_gdt, @function

set_gdt:
    pushl %ebp
    movl  %esp, %ebp

    # set the new gdt
    movl  8(%ebp), %eax
    lgdtl (%eax)

    # reload the segment registers
    movl  12(%ebp), %eax
    movl  16(%ebp), %ecx

    movl  $.reload_cs, .ljmp_addr
    movw  %ax, .ljmp_addr + 4 

    ljmp  *.ljmp_addr 
.reload_cs:
    nop

    movw  %cx, %ds
    movw  %cx, %es
    movw  %cx, %fs
    movw  %cx, %gs
    movw  %cx, %ss

    movl  %ebp, %esp
    popl  %ebp
    ret
