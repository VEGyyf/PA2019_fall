#include <stdio.h>
#include <stdlib.h>
#include "cpu/instr.h"

make_instr_func(lidt)
{
    OPERAND m;
	m.data_size = data_size;
    m.sreg=SREG_ES;
    m.addr=eip+2;
    m.type=OPR_IMM;
	operand_read(&m);
    cpu.gdtr.limit=paddr_read(m.val,2);
    uint32_t bs=0;
    if(data_size==16){
        cpu.gdtr.base=paddr_read(m.val+16,3);
        memset(&bs+3,0,1);
    }
    else if(data_size==32)
    cpu.gdtr.base=paddr_read(m.val+16,4);//bs;   
	print_asm_1("lgdt", "", 2+data_size/8, &m);
	return 2+data_size/8;
}
