# regdump.S - asm function to dump all registers
# Ben Staehle - 8/32/25
.code32

.section .data

temp_esp: .long 0

.section .text

get_pc:
    call .Lget_pc
.Lget_pc:
    popl %eax
    ret

.globl dump_regs
.type dump_regs, @function

dump_regs:
    # save the temp esp
    movl %esp, temp_esp

    pushl %ebp
    movl  %esp, %ebp
    
    # load the struct pointer into edx
    pushl %edx
    mov   8(%ebp), %edx  
    
    # save the registers
    movl  %eax, 0(%edx)
    movl  %ecx, 4(%edx)
    
    # get %edx
    popl  %eax
    movl  %eax, 8(%edx)

    movl  %ebx, 12(%edx)
    movl  %ebp, 16(%edx)

    # get the saved esp
    movl temp_esp, %eax
    movl %eax, 20(%edx)

    movl  %esi, 24(%edx)
    movl  %edi, 28(%edx)

    # get crX regs
    movl  %cr0, %eax
    movl  %eax, 32(%edx)
    movl  %cr2, %eax
    movl  %eax, 36(%edx)
    movl  %cr3, %eax
    movl  %eax, 40(%edx)

    # get %eip
    call  get_pc
    movl  %eax, 44(%edx)

    movl %ebp, %esp
    popl %ebp
    ret
    


