#include "cpu/instr.h"

make_instr_func(leave)
{
    int len = 1;           //mov ebp, esp      
                                                                                                      \
    OPERAND src,dest;
    src.type=dest.type=OPR_REG;
    src.data_size=dest.data_size=data_size;
    src.addr=cpu.ebp;
    dest.addr=cpu.esp;
    operand_read(src);
	dest.val = src.val;
	operand_write(dest);                                                                                                 \
	opr_dest.data_size=data_size;// pop ebp;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);
    src.val=opr_dest.val;
    operand_write(&opr_src);
	cpu.esp+=4;                                                                                                          \
    return len;     
}

