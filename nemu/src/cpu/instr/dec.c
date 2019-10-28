#include "cpu/instr.h"

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    uint32_t temp=cpu.eflags.CF;
    opr_src.val=alu_sub(opr_src.val,1,opr_dest.data_size);
	cpu.eflags.CF=temp;
    operand_write(&opr_src);
}

make_instr_impl_1op(dec, r, v)
make_instr_impl_1op(dec, rm, v)
