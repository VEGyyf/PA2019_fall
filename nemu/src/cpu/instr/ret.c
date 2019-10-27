#include "cpu/instr.h"

make_instr_func(ret_near)
{
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    opr_src.addr=eip;
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);
    return 1 ;//the length of opr=1
}
/*
pop:
static void instr_execute_1op() 
{
   //OPERAND src, res;  

    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);
	cpu.esp+=4;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, i, v)
make_instr_impl_1op(pop, i, b)
*/
