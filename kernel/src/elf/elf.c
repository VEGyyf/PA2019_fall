#include "common.h"
#include "memory.h"
#include "string.h"

#include <elf.h>

#ifdef HAS_DEVICE_IDE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader()
{
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph, *eph;

#ifdef HAS_DEVICE_IDE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void *)buf;
	Log("ELF loading from hard disk.");
#else
	elf = (void *)0x0;// 模拟内存 0x0 处是 RAM Disk ，存放的就是 testcase ELF file
	Log("ELF loading from ram disk.");
#endif



   
	/* Load each program segment */
	ph = (void *)elf + elf->e_phoff;// 找到 ELF 文件中的程序头表
	eph = ph + elf->e_phnum;

 
	for (; ph < eph; ph++)
	{// 扫描程序头表中的各个表项
		if (ph->p_type == PT_LOAD)
		{// 如果类型是 LOAD ，那么就去装载吧
            uint32_t paddr=mm_malloc(ph->p_vaddr,ph->p_memsz);
            ide_read((void *)paddr,ELF_OFFSET_IN_DISK+ph->p_offset,ph->p_filesz);
           // uint32_t addr=ph->p_vaddr;    
			// remove this panic!!!
			//panic("Please implement the loader");
            //void* dest=(void*)addr;//ph->p_vaddr;
            //void* src=(void*)(ph->p_offset);
/* TODO: copy the segment from the ELF file to its proper memory area */
           // memcpy(dest, src, ph->p_filesz);
/* TODO: zero the memory area [vaddr + file_sz, vaddr + mem_sz) */
            void* dest_set=(void*)(addr+ph->p_filesz);//(ph->p_vaddr+ph->p_filesz);
            memset(dest_set,0,ph->p_memsz-ph->p_filesz);
#ifdef IA32_PAGE
			/* Record the program break for future use */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if (brk < new_brk)
			{
				brk = new_brk;
			}
            //ph->p_paddr = mm_malloc(ph->p_vaddr, ph->p_memsz);
#endif
		}
	}

	volatile uint32_t entry = elf->e_entry;// 头文件中指出的 testcase 起始地址，应该是 0x60000

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);
#ifdef HAS_DEVICE_VGA
	create_video_mapping();
#endif
	write_cr3(get_ucr3());
#endif
	return entry;// 返回 testcase 起始地址，在 init_cond 后面执行 ((void(*)( eip
}
