#include "cpu/instr.h"

make_instr_func(leave)
{
    int len = 1;                                                                                                                       \
    OPERAND src,dest;
    src.type=dest.type=OPR_REG;
    src.data_size=dest.data_size=data_size;
    src.addr=cpu.ebp;
    dest.addr=cpu.esp;
    operand_read(src);
	dest.val = src.val;
	operand_write(dest);                                                                                                 \
		                                                                                                             \
    return len;     
}

