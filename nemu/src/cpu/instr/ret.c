#include "cpu/instr.h"

make_instr_func(ret_near)
{
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    opr_src.addr=cpu.eip;
    opr_src.type=OPR_REG;
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);
    cpu.esp+=4;
    cpu.eip=opr_dest.val;
    return 0 ;//the length of opr=0
}

