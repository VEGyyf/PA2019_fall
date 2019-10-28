#include "cpu/instr.h"

static void instr_execute_2op() 
{
   
	operand_read(&opr_src);
    operand_read(&opr_dest);
    //uint32_t src=opr_src.val;
    opr_src.val=sign_ext(opr_src.val & (0xFFFFFFFF >> (32 - opr_src.data_size)),32);
    opr_dest.val=sign_ext(opr_dest.val & (0xFFFFFFFF >> (32 - opr_dest.data_size)),32);
	opr_dest.val = alu_and(opr_src.val,opr_dest.val,32);
	operand_write(&opr_dest);
}

make_instr_impl_2op(and, r, rm, b)
make_instr_impl_2op(and, r, rm, v)
make_instr_impl_2op(and, rm, r, b)
make_instr_impl_2op(and, rm, r, v)
make_instr_impl_2op(and, i, a, b)
make_instr_impl_2op(and, i, a, v)
make_instr_impl_2op(and, i, rm, bv)
make_instr_impl_2op(and, i, rm, v)
make_instr_impl_2op(and, i, rm, b)
