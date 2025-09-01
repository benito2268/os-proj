# regdump.S - asm function to dump all registers
# Ben Staehle - 8/32/25

.code32

.section .text

get_pc:
    call .Lget_pc
.Lget_pc:
    popl %eax
    ret

.globl dump_regs
.type dump_regs, @function

dump_regs:
    pushl %ebp
    movl  %esp, %ebp

    # push all registers
    pushal
    pushl %cr0
    pushl %cr2
    pushl %cr3
    pushf

    # get the value of %eip
    call get_pc
    pushl %eax

    # return a pointer to the struct
    movl %esp, %eax
    
    movl %ebp, %esp
    popl %ebp
    ret
    


