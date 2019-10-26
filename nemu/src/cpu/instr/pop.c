#include "cpu/instr.h"

static void instr_execute_1op() 
{
   //OPERAND src, res;  
	//operand_read(&opr_src);
    opr_src.addr=esp;
    opr.dest.val=opr.src.val;
    operand_write(&opr_dest);
	cpu.esp+=4;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
make_instr_impl_1op(pop, i, b)

