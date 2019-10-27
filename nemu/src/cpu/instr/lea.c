#include "cpu/instr.h"

make_instr_func(lea)
{
       OPERAND src,dest;
       src.data_size = dest.data_size = data_size; // 指定操作数长度 
       int len = 1;
       len += modrm_r_rm(eip + 1,  &dest, &src); // 操作数寻址
       dest.val = src.addr; 
       operand_write(&dest);
       return len;
}
/* 
make_instr_func(mov_r2rm_v) { 
OPERAND r, rm;
rm.data_size = r.data_size = data_size; // 指定操作数长度 
int len = 1;
len += modrm_r_rm(eip + 1, &r, &rm); // 操作数寻址
operand_read(&r); // mov 操作 
rm.val = r.val; 
operand_write(&rm);
return len;}
*/
