#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include "memory/cache.h"
#include <memory.h>
#include <stdio.h>


uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
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

    ///*TODO*/cache_read();
	//uint32_t ret = 0;
	//ret = hw_mem_read(paddr, len);
	//return ret;*/
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED     
/*TODO*/cache_write(paddr,len,data,L1_dcache);
#else
	hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
	return paddr_read(laddr, len);
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
	paddr_write(laddr, len, data);
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return laddr_read(vaddr, len);
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
	laddr_write(vaddr, len, data);
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
