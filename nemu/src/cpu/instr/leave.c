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
    
	cpu.esp+=4;    //pop ebp
     print_asm_0("leave","",len);                                                                                                     
    return len;     
}
/*pop:
   opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    opr_src.val=opr_dest.val;
    operand_write(&opr_src);
	cpu.esp+=4;*/
