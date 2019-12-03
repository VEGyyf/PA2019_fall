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
    uint32_t addr=cpu.gdtr.base+(cpu.segReg[sreg].index*8);
    SegDesc temp;//memcpy?
    memcpy(&temp,addr,8);
    //memcpy((&temp.limit)+2,addr+6,2);
    //memcpy((&temp.limit),addr,2);
    //memcpy((&temp.limit),addr,2);
    //memcpy((&temp.limit),addr,2);
    //memcpy((&temp.limit),addr,2);
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

    cpu.segReg[sreg].base=bs;
    cpu.segReg[sreg].limit=lmt;
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
