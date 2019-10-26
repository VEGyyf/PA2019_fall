#include "cpu/instr.h"

static void instr_execute_1op() 
{
   //OPERAND src, res;  
	operand_read(&opr_src);
    opr_dest.addr=opr_src.addr;
    opr_src.addr=cpu.esp;
    opr_dest.val=opr_src.val;
    operand_write(&opr_dest);
	cpu.esp+=4;
}

make_instr_impl_1op(pop, rm, v)
make_instr_impl_1op(pop, i, v)
make_instr_impl_1op(pop, i, b)

