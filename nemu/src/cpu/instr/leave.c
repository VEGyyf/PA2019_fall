#include "cpu/instr.h"

make_instr_func(leave)
{
    int len = 1;           //mov ebp, esp      
    OPERAND src,dest;//,temp;
    src.type=OPR_REG;
    dest.type=OPR_MEM;
    //temp.type=OPR_MEM;
    src.data_size=dest.data_size=temp.data_size=data_size;
    src.addr=cpu.ebp;
    dest.addr=cpu.esp;
    //temp.addr=cpu.esp;
    operand_read(&src);
	dest.val = src.val;
	operand_write(&dest);                                                                                                 
	operand_read(&tdest);
    cpu.ebp=dest.val;
    //operand_write(&src);
	cpu.esp+=4;    
     print_asm_0("leave","",len);                                                                                                     
    return len;     
}

