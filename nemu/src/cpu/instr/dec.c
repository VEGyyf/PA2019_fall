#include "cpu/instr.h"

static void instr_execute_1op() 
{
    operand_read(&opr_src);
     opr_src.val=sign_ext(opr_src.val, opr_src.data_size); 
    uint32_t temp=cpu.eflags.CF;
    uint32_t dec=1;
    opr_src.val=alu_sub(dec,opr_src.val,opr_src.data_size);
	cpu.eflags.CF=temp;
    operand_write(&opr_src);
}

make_instr_impl_1op(dec, r, v)
make_instr_impl_1op(dec, rm, v)
