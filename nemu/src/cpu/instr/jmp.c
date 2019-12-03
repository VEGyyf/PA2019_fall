#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_far_imm)//TODO:change CS,段间绝对转移
{
        OPERAND obj;
        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        int len=1;
        len+=modrm_rm(eip+1,&obj);
        operand_read(&obj);
        /*uint32_t csval=(obj.val>>5);
        uint32_t ipval=(obj.val&(0xffffffff));
        cpu.eip = ipval;
        cpu.cs.val=csval;*/
        memcpy((&cpu.eip),&obj.val,4);
        memcpy((&cpu.cs.val),&obj.val+4,2);   
        //uint8_t idx=obj.addr&0xf;     
        load_sreg(cpu.cs.index);
        print_asm_1("ljmp", "", len, &obj);
        


        return 0;
}

make_instr_func(jmp_short)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = 8;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, 8);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 2, &rel);

        cpu.eip += offset;

        return 2;
}

make_instr_func(jmp_near_indirect)
{
        OPERAND obj;

        obj.sreg = SREG_CS;
        obj.data_size = data_size;
        int len=1;
        len+=modrm_rm(eip+1,&obj);

        operand_read(&obj);


        print_asm_1("jmp", "", len, &obj);
        
        cpu.eip = obj.val;

        return 0;
}
