#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
    uint32_t dir=laddr>>22;
    uint32_t dir_offset=dir<<2;
    uint32_t dir_bs=cpu.cr3.pdbr<<12;
    PDE temp_dir;//memcpy?
    memcpy(&temp_dir,hw_mem+dir_bs+dir_offset,4);//uint32_t?4B?

    uint32_t page_frame=temp_dir.page_frame;
    

    uint32_t page=((laddr>>12)&0x3ff);//(0xffffffff>>(32-10))
    uint32_t offset=laddr&0x7ff;//(0xffffffff>>(32-11))
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
