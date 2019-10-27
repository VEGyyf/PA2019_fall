#include "cpu/instr.h"

make_instr_func(ret_near)
{
    opr_dest.data_size=32;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.eip=opr_dest.val;
    cpu.esp+=4;
    return 0 ;//the length of opr=0
}

