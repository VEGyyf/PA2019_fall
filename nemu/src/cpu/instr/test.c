#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = alu_ test(opr_dest.val,opr_src.val,opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op( test, r, rm, b)
make_instr_impl_2op( test, r, rm, v)
make_instr_impl_2op( test, rm, r, b)
make_instr_impl_2op( test, rm, r, v)
make_instr_impl_2op( test,i,a,b)
make_instr_impl_2op( test,i,a,v)
make_instr_impl_2op( test,i,rm,bv)
make_instr_impl_2op( test,i,rm,v)
make_instr_impl_2op( test,i,rm,b)
