#include "cpu/instr.h"

static void instr_execute_1op() 
{
   
	opr_src.val=~opr_src.val;
}

make_instr_impl_1op(not, rm, b)
make_instr_impl_1op(not, rm, v)
