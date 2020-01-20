#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"
#include <memory.h>
#include <stdio.h>

#define SIZE 4096

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
    int map_no=ismm_io(paddr);
    uint32_t ret = 0;
    if(map_no==-1){
	memcpy(&ret, hw_mem + paddr, len);
    }
    else {
    ret= mmio_read(hw_mem + paddr, len, map_no)
    }
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
    int map_no=ismm_io(paddr);
    if(map_no==-1){
	memcpy(hw_mem + paddr, &data, len);
    }
     else {
    
    }
}

uint32_t paddr_read(paddr_t paddr, size_t len)
{
    uint32_t ret=0;
#ifdef CACHE_ENABLED
             ret=cache_read(paddr,len,L1_dcache);
#else
             ret=hw_mem_read(paddr,len);
#endif
    return ret;

}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED     
    cache_write(paddr,len,data,L1_dcache);
#else
	hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
    if(cpu.cr0.pg==1&&cpu.cr0.pe==1 ){//CR0 什么状态
      // if (laddr%SIZE+len>SIZE) {//data cross the page boundary
                /* this is a special case, you can handle it later. */
        //                 assert(0);
        //} else {
        paddr_t paddr = page_translate(laddr);
        return paddr_read(paddr,len);
        //}
    }else {
         return paddr_read(laddr,len);
    }
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
    assert(len == 1 || len == 2 || len == 4);
    if(cpu.cr0.pg==1&&cpu.cr0.pe==1 ){//CR0 什么状态
        //if (laddr%SIZE+len>SIZE) {//data cross the page boundary
                /* this is a special case, you can handle it later. */
                           ;//assert(0);
        //} else {
        paddr_t paddr = page_translate(laddr);
        paddr_write(paddr,len,data);
        //}
    }else {
         paddr_write(laddr,len,data);
    }
	//paddr_write(laddr, len, data);
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	#ifndef IA32_SEG
        return laddr_read(vaddr, len);
   #else
        uint32_t laddr = vaddr;
        if( cpu.cr0.pe==1){
            laddr = segment_translate(vaddr, sreg);
        }
        return laddr_read(laddr, len);
    #endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
	laddr_write(vaddr, len, data);
    #ifndef IA32_SEG
        laddr_write(vaddr, len, data);
    #else
        uint32_t laddr = vaddr;
        if( cpu.cr0.pe==1){
            laddr = segment_translate(vaddr, sreg);
        }
        laddr_write(laddr, len, data);
    #endif
}

void init_mem()
{
#ifdef CACHE_ENABLED     
    init_cache();
#else
	memset(hw_mem, 0, MEM_SIZE_B);
#endif        
    
	// clear the memory on initiation
    //加入条件编译选项以便日后通过修改 include/ config.h 来跳过 cache 相关代码.具体仿照教程中（或后页）针对 paddr_read 和 paddr_write 的修改方法
	

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
/*可以设置一个简单的模拟计时器，如果 cache 命中则时间 +10
cache 缺失则时间 +100 ，比较一下模拟的时间消耗有什么变化

也可以加入对 cache 命中率的统计*/
