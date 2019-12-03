#include <stdio.h>
#include <stdlib.h>
#include "cpu/instr.h"

make_instr_func(lgdt)
{
    OPERAND m;
	m.data_size = data_size;
    m.sreg=SREG_ES;
    m.addr=eip+3;
    m.type=OPR_IMM;
	operand_read(&m);
    uint32_t lmt=0;
    memcpy(&lmt,hw_mem+m.val,2);
    cpu.gdtr.limit=lmt;
    uint32_t bs=0;
    if(data_size==16){
        memcpy(&bs,hw_mem+m.val+16,3);
        //memset(&bs+3,0,1);
    }
    else if(data_size==32)memcpy(&bs,hw_mem+m.val+16,4);
    cpu.gdtr.base=bs;   
    assert(lmt==0xfffff);
	print_asm_1("lgdt", "", 3+data_size/8, &m);
	return 3+data_size/8;
}


/*ELSE (* instruction = LGDT *)
IF OperandSize = 16

THEN GDTR.Limit:Base    ← m16:24 (* 24 bits of base loaded *)

ELSE GDTR.Limit:Base    ← m16:32;
FI;
FI;
将源操作数中的值加载到全局描述符表格寄存器 (GDTR) 。源操作数指定 6 字节(48 bit)内存位置，它包含全局描述符表格 (GDT)  的基址（线性地址）与限制（表格大小，以字节计）。如果操作数大小属性是 32 位，则将 16 位限制（6 字节数据操作数的 2 个低位字节）与 32 位基址（数据操作数的 4 个高位字节）加载到寄存器。如果操作数大小属性是 16 位，则加载 16 位限制（2 个低位字节）与 24 位基址（第三、四、五字节）。这里，不使用操作数的高位字节，GDTR 或 IDTR 中基址的高位字节用零填充。*/
