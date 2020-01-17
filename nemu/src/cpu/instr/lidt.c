#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(lidt)
{
    OPERAND m;
    modrm_rm(eip+1,&m);
    cpu.idtr.limit=laddr_read(m.addr,2);
    cpu.idtr.base=laddr_read(m.addr+2,4);//bs;  
	/*m.data_size = data_size;
    m.sreg=SREG_ES;
    m.addr=eip+2;
    m.type=OPR_IMM;
	//int len=2;
    //len+=modrm_rm(eip+2,&m);
	operand_read(&m);
    //uint32_t lmt=0;
    //memcpy(&lmt,hw_mem+m.val,2);
    cpu.gdtr.limit=paddr_read(m.val,2);//lmt;
    uint32_t bs=0;
    if(data_size==16){
        cpu.gdtr.base=paddr_read(m.val+16,3);//memcpy(&bs,hw_mem+m.val+16,3);
        memset(&bs+3,0,1);
    }
    else if(data_size==32)//memcpy(&bs,hw_mem+16,4);
    cpu.gdtr.base=paddr_read(m.val+16,4);//bs;   
    //assert(lmt==0xfffff);
	print_asm_1("lgdt", "", 2+data_size/8, &m);*/
    print_asm_1("lidt", "", 2+data_size/8, &m);
	return 2+data_size/8;
}
