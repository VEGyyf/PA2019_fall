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
    temp_dir.val=paddr_read(dir_bs+dir_offset,4);//memcpy(&temp_dir,hw_mem+dir_bs+dir_offset,4);//uint32_t?4B?

    uint32_t page_frame=temp_dir.page_frame;
    uint32_t pg_bs=page_frame<<12;

    uint32_t page=((laddr>>12)&0xffffffff>>(32-10));
    uint32_t pg_offset=page<<2;
    PTE temp_pg;//memcpy?
    temp_pg.val=paddr_read(pg_bs+pg_offset,4);//memcpy(&temp_pg,hw_mem+pg_bs+pg_offset,4);//uint32_t?4B?

   // assert(temp_pg.present==1);
    uint32_t paddr_bs=temp_pg.page_frame;
    paddr_bs<<=12;
    uint32_t offset=laddr&0xfff;//12!!
	uint32_t res=paddr_bs|offset;//printf("\nPlease implement page_translate()\n");
	return res;//assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
