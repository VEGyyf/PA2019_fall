#include "cpu/instr.h"

make_instr_func(call_near)
{
        cpu.esp-=data_size/8;
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

make_instr_func(call_near_indirect)
{
     

        OPERAND obj;
        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        int len=1;
        len+=modrm_rm(eip+1,&obj);

        operand_read(&obj);
   
        cpu.esp-=data_size/8;
        opr_dest.type=OPR_MEM;
        opr_dest.addr=cpu.esp;
        opr_dest.val=eip+len+1;
        operand_write(&opr_dest);//push ret_addr
        //int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", len, &obj);

        cpu.eip =obj.val;

        return 0;//=jmp,跳转到指定地址
}

/*make_instr_func(jmp_near_indirect)
{
        OPERAND obj;
        //obj.type = OPR_MEM;
        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        int len=1;
        len+=modrm_rm(eip+1,&obj);
       // obj.addr = eip + 1;
        operand_read(&obj);

        //int ea = sign_ext(obj.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", len, &obj);
        
        cpu.eip = obj.val;

        return 0;
}*/
