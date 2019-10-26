#include "cpu/instr.h"

static void instr_execute_1op() 
{
   //OPERAND src, res;  

    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    opr_src.val=opr_de.val;
    operand_write(&opr_src);
	cpu.esp+=4;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
make_instr_impl_1op(pop, i, b)

