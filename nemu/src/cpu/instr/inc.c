#include "cpu/instr.h"

static void instr_execute_1op() 
{
   opr_src.val=alu_add(1,opr_src.val,opr_dest.data_size);
	
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)
