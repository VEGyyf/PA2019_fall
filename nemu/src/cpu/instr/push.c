#include "cpu/instr.h"

static void instr_execute_1op() 
{
    //OPERAND res;  
	operand_read(&opr_src);
	cpu.esp-=4;
    opr_desr.addr=esp;
    opr_dest.val=opr.src.val;
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, i, v)
make_instr_impl_1op(push, i, b)

