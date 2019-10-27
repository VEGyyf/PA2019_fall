#include "cpu/instr.h"

static void instr_execute_1op() 
{
    uint32_t temp=cpu.eflags.CF;
   opr_src.val=alu_add(1,opr_src.val,opr_dest.data_size);
	cpu.eflags.CF=temp;
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)
