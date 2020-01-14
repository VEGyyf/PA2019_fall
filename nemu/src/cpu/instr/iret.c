#include "cpu/instr.h"

make_instr_func(iret)
{
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_SS;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.eip=opr_dest.val;
	cpu.esp+=data_size/8;//eip<--pop()
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_CS;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.cs=opr_dest.val;
	cpu.esp+=data_size/8;//cs ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.eflags=opr_dest.val;
	cpu.esp+=data_size/8;//BP ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
	cpu.esp+=data_size/8;//throwaway ← Pop (); (* Skip esp *)
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.bx=opr_dest.val;
	cpu.esp+=data_size/8;//BX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.dx=opr_dest.val;
	cpu.esp+=data_size/8;//DX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.cx=opr_dest.val;
	cpu.esp+=data_size/8;//CX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.ax=opr_dest.val;
	cpu.esp+=data_size/8;//AX ← Pop();
    //cs<--pop()
    //eflags<--pop()
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
