#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = alu_sbb(opr_dest.val,opr_src.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sbb, r, rm, b)
make_instr_impl_2op(sbb, r, rm, v)
make_instr_impl_2op(sbb, rm, r, b)
make_instr_impl_2op(sbb, rm, r, v)
make_instr_impl_2op(sbb, i, a, b)
make_instr_impl_2op(sbb, i, a, v)
make_instr_impl_2op(sbb, i, rm,bv)
make_instr_impl_2op(sbb, i, rm,v)
make_instr_impl_2op(sbb, i, rm,b)
