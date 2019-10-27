#include "cpu/instr.h"

make_instr_func(call_near)
{
        cpu.esp-=4;
        opr_dest.type=OPR_MEM;
        opr_dest.addr=cpu.esp;
        opr_dest.val=eip+5;
        operand_write(&opr_dest);//push ret_addr

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

