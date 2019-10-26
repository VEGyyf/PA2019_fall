#include "cpu/instr.h"

static void instr_execute_1op() 
{
   //OPERAND src, res;  
	operand_read(&opr_src);
	cpu.esp-=4;
    opr_dest.addr=esp;
    opr.dest.val=opr.src.val;
    operand_write(&opr_dest);
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
make_instr_impl_1op(pop, i, b)

