#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(iret)
{
    cpu.eip=vaddr_read(cpu.esp,SREG_SS, 4);//vaddr_write(cpu.eip,SREG_SS,4,cpu.esp);//Pop()-->eip;
    printf("eip=0x%x",cpu.eip);
	cpu.esp+=data_size/8;
    cpu.cs.val=vaddr_read(cpu.esp,SREG_SS, 2);//Pop()-->cs;
	cpu.esp+=data_size/8;
    cpu.eflags.val=vaddr_read(cpu.esp,SREG_SS, 4);//Pop()-->eflags;
	cpu.esp+=data_size/8;
    //cpu.eip=;
    print_asm_0("iret", "", 1);
    return 0 ;
}
/*
通过iret 指令恢复最初被保护的程序断点和状态信息，返回原程序被中断的指令（或下一条，根据保护断点时具体保存的EIP 决定）继续执行。

eip<--pop()
cs<--pop()
eflags<--pop()

?16?32?va?pa?pe?
*/
/*int_
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);//Push(EFLAGS);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,2,cpu.cs.val);//Push(CS);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);//Push(EIP);*/
