#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
    operand_read(&opr_dest);
    uint32_t temp_1= opr_dest.val;
    uint32_t temp_2= opr_src.val;
= alu_and(opr_src.val,opr_dest.val,opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op( test, r, rm, b)
make_instr_impl_2op( test, r, rm, v)
make_instr_impl_2op( test,i,a,b)
make_instr_impl_2op( test,i,a,v)
make_instr_impl_2op( test,i,rm,v)
make_instr_impl_2op( test,i,rm,b)
