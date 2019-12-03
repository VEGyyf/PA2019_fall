#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
    uint32_t bs =cpu.segReg[sreg].base;
    uint32_t res=offset+bs;
	return res;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
    void * addr=gdtr.base+(cpu.segReg[sreg].index*8);
    SegDesc temp;//memcpy?
    memcpy((&temp.limit),addr,2);
    
    cpu.segReg[sreg].base=temp.base;
    cpu.segReg[sreg].limit=temp.limit;
    cpu.segReg[sreg].type=temp.type;
    cpu.segReg[sreg].privilege_level=temp.privilege_level;
    cpu.segReg[sreg].soft_use=temp.soft_use;
/*
            uint32_t base;
            uint32_t limit;
            uint32_t type :5;
            uint32_t privilege_level :2;
            uint32_t soft_use :1;*/
}
