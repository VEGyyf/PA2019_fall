#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);
	cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_REG;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_SS;
    opr_dest.val=cpu.eflags.val;
    operand_write(&opr_dest);//Push(EFLAGS);
	cpu.esp-=data_size/8;
    opr_dest.addr=cpu.esp;
    opr_dest.val=cpu.cs.base;
    operand_write(&opr_dest);//Push(CS);
	cpu.esp-=data_size/8;opr_dest.addr=cpu.esp;
    opr_dest.val=cpu.eip;
    operand_write(&opr_dest);//Push(EIP);
    if(intr_no>=32)cpu.eflags.IF=0;// Clear IF if it is an interrupt
    uint32_t entry;// Trigger an exception/interrupt with 'intr_no'
    uint32_t temp=cpu.idtr.base+intr_no*8;// 'intr_no' is the index to the IDT
    uint32_t selector=temp>>16;
    uint32_t offset=temp;
    entry=selector+offset;
    cpu.eip=entry;// Set EIP to the entry of the interrupt handler//跳转执行
// Trigger an exception/interrupt with 'intr_no'
// 'intr_no' is the index to the IDT
// Push EFLAGS, CS, and EIP
// Find the IDT entry using 'intr_no'
// Clear IF if it is an interrupt
// Set EIP to the entry of the interrupt handler//跳转执行
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
