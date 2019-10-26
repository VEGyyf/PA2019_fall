#include "cpu/instr.h"

static void instr_execute_1op() 
{
    //OPERAND res;  
	operand_read(&opr_src);
	cpu.esp-=4;
    opr_dest.type=OPR_REG;
    opr_dest.addr=cpu.esp;
    opr_dest.val=opr_src.val;
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, i, v)
make_instr_impl_1op(push, i, b)
/*#define decode_operand_r    \
	opr_src.type = OPR_REG; \
	opr_src.addr = opcode & 0x7;*/
