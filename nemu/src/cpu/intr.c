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
    //printf("esp=0x%x",cpu.esp);
    //printf("eip=0x%x",cpu.eip);

    GateDesc desc;// Trigger an exception/interrupt with 'intr_no','intr_no' is the index to the IDT
    uint32_t temp[2];//little endian 
    temp[0]=laddr_read(cpu.idtr.base+intr_no*8,4);
    temp[1]=laddr_read(cpu.idtr.base+4+intr_no*8,4);
    memcpy(&desc,temp,8);

    if(desc.type==15)cpu.eflags.IF=0;// Clear IF if it is an interrupt

    cpu.cs.val=desc.selector;
    SegDesc tmp;// load cs
    uint32_t temp2[2];
    temp2[0]=laddr_read(cpu.gdtr.base+cpu.cs.index*8,4);
    temp2[1]=laddr_read(cpu.gdtr.base+cpu.cs.index*8+4,4);
    memcpy(&tmp,temp2,8);
    uint32_t base_31_24 =tmp.base_31_24;
    uint32_t base_23_16 =tmp.base_23_16 ;
    uint32_t base_15_0=tmp.base_15_0;
    base_31_24<<=24;
    base_23_16<<=16;
    uint32_t bs=base_15_0|base_23_16;
    bs=bs|base_31_24;

    uint32_t limit_15_0=tmp.limit_15_0;
    uint32_t limit_19_16=tmp.limit_19_16;
    limit_19_16<<=16;
    uint32_t lmt=limit_19_16|limit_15_0;
    cpu.cs.base=bs;
    cpu.cs.limit=lmt;
    cpu.cs.type=tmp.type;
    cpu.cs.privilege_level=tmp.privilege_level;
    cpu.cs.soft_use=tmp.soft_use;



   
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
