#include "cpu/instr.h"

make_instr_func(call_near)
{
        OPERAND ret_addr;
        ret_addr.type=OPR_IMM;
        ret_addr.addr=eip;
        operand_read(&ret_addr);
        cpu.esp-=4;
        opr_dest.type=OPR_MEM;
        opr_dest.addr=cpu.esp;
        opr_dest.val=opr_ret_addr.val;
        operand_write(&opr_dest);

        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;//=jmp,跳转到指定地址
}
/*operand_read(&opr_src);
	cpu.esp-=4;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.val=opr_src.val;
    //len + = modrm_r_rm(eip + 1, &opr_src, &opr_dest); 
    operand_write(&opr_dest);*/
/*make_instr_func(call_near_indirect)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("call", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}*/
