#include "cpu/instr.h"

static void instr_execute_1op() 
{
   
	operand_read(&opr_src);
	cpu.esp-=4;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.val=opr_src.val;
    //len + = modrm_r_rm(eip + 1, &opr_src, &opr_dest); 
    operand_write(&opr_dest);
}

make_instr_impl_1op(not, rm, b)
make_instr_impl_1op(not, rm, v)
