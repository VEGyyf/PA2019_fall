#include "cpu/instr.h"

make_instr_func(leave)
{
    int len = 1;        
    cpu.esp=cpu.ebp;//mov ebp, esp    
     
    OPERAND dest;
    dest.data_size=data_size;
    dest.type=OPR_MEM;
    dest.addr=cpu.esp;
   
	                                                                                                
	operand_read(&dest);
    cpu.ebp=dest.val;
    
	cpu.esp+=data_size/8;    //pop ebp
     print_asm_0("leave","",len);                                                                                                     
    return len;     
}

