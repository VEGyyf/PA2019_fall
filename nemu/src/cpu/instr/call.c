#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(call_near)
{
    operand_read(&opr_src);
    cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,opr_src.val);//push ret_addr


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

make_instr_func(call_near_indirect)
{
         operand_read(&opr_src);
    cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,opr_src.val);//push ret_addr

        OPERAND obj;
        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        obj.addr=eip+1;

        operand_read(&obj);
   
      
        //int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", 1 + data_size / 8, &obj);

        cpu.eip =obj.val;

        return 0;//=jmp,跳转到指定地址
}


