#include "cpu/instr.h"

make_instr_func(popa)
{
    uint8_t len=1;
    opr_dest.data_size=data_size;//!!initialize
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    print_asm_0("ret","",len);
    cpu.eip=opr_dest.val;
    cpu.esp+=data_size/8;
    return 0 ;//the length of opr=0
}
