#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(call_near)
{
    cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);//push ret_addr


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
    cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);//Push(EIP);

        OPERAND obj;
        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        obj.addr=eip+1;
        obj.type=OPR_MEM;
        operand_read(&obj);
        cpu.eip =obj.val;
      
        //int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", 1 + data_size / 8, &obj);

       

        return 0;//=jmp,跳转到指定地址
}


