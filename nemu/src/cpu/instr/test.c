#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
    operand_read(&opr_dst);
    uint32_t temp = alu_and(opr_src.val,opr_dest.val,opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op( test, r, rm, b)
make_instr_impl_2op( test, r, rm, v)
make_instr_impl_2op( test,i,a,b)
make_instr_impl_2op( test,i,a,v)
make_instr_impl_2op( test,i,rm,v)
make_instr_impl_2op( test,i,rm,b)
