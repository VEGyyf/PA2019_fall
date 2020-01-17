#include "cpu/instr.h"
#include "memory/memory.h"

static void instr_execute_1op() 
{
   
	operand_read(&opr_src);
	cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.sreg=SREG_SS;
    opr_dest.type=OPR_REG;
    opr_dest.addr=cpu.esp;
    opr_dest.val=opr_src.val;
    //len + = modrm_r_rm(eip + 1, &opr_src, &opr_dest); 
    operand_write(&opr_dest);

    cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, i, v)
make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, rm, v)

