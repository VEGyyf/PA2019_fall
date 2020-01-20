#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(call_near)
{
    OPERAND rel;
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_SS,4,eip+data_size/8+1);//push eip
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;
	operand_read(&rel);
	print_asm_1("call", "", 1, &rel);
	cpu.eip+=rel.val+data_size/8+1;

	return 0;

}

make_instr_func(call_near_indirect)
{
	int len=1;
	OPERAND obj;
	cpu.esp-=4;
	len+=modrm_rm(eip + 1, &obj);
    obj.data_size = data_size;
	operand_read(&obj);

	print_asm_1("call", "", 1, &obj);
	vaddr_write(cpu.esp,SREG_SS,4,eip+len);//push eip
	cpu.eip=obj.val;//=jmp,跳转到指定地址*/
	return 0;   
}


