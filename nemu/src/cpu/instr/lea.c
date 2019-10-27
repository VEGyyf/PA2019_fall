#include "cpu/instr.h"

make_instr_func(lea)
{
       opr_dest.data_size = opr_src.data_size = data_size; // 指定操作数长度 
       int len = 1;
       len += modrm_r_rm(eip + 1, &opr_src, &opr_dest); // 操作数寻址
       //operand_read(&opr_src); 
       opr_dest.val = opr_src.addr; 
       operand_write(&opr_dest);
       return len;
}
/*make_instr_func(mov_rm2r_b) { 
OPERAND r, rm;
r.data_size = rm.data_size = 8; // 指定操作数长度
int len = 1; len += modrm_r_rm(eip + 1, &r, &rm); // 操作数寻址
operand_read(&rm);// mov 操作 r.val = rm.val; operand_write(&r);
return len; 
}
make_instr_func(mov_r2rm_v) { OPERAND r, rm;
rm.data_size = r.data_size = data_size; // 指定操作数长度 
int len = 1;
len += modrm_r_rm(eip + 1, &r, &rm); // 操作数寻址
operand_read(&r); // mov 操作 
rm.val = r.val; 
operand_write(&rm);
return len;}
*/
