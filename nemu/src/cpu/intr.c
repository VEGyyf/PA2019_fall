#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);//Push(EFLAGS);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,2,cpu.cs.val);//Push(CS);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);//Push(EIP);


    SegDesc temp;// load cs
    memcpy(&temp,hw_mem+cpu.gdtr.base+(cpu.cs.index*8),8);
    uint32_t base_31_24 =temp.base_31_24;
    uint32_t base_23_16 =temp.base_23_16 ;
    uint32_t base_15_0=temp.base_15_0;
    base_31_24<<=24;
    base_23_16<<=16;
    uint32_t bs=base_15_0|base_23_16;
    bs=bs|base_31_24;

    uint32_t limit_15_0=temp.limit_15_0;
    uint32_t limit_19_16=temp.limit_19_16;
    limit_19_16<<=16;
    uint32_t lmt=limit_19_16|limit_15_0;
    cpu.cs.base=bs;
    cpu.cs.limit=lmt;
    cpu.cs.type=temp.type;
    cpu.cs.privilege_level=temp.privilege_level;
    cpu.cs.soft_use=temp.soft_use;


    if(intr_no==15)cpu.eflags.IF=0;// Clear IF if it is an interrupt

    GateDesc desc;// Trigger an exception/interrupt with 'intr_no'
    memcpy(&desc,hw_mem+cpu.idtr.base+(intr_no*8),8);// 'intr_no' is the index to the IDT
    cpu.cs.val=desc.selector;
    cpu.eip=desc.offset_15_0|(desc.offset_31_16<<16);
// Set EIP to the entry of the interrupt handler//跳转执行
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
