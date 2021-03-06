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
        obj.addr=eip+1;
        obj.type=OPR_IMM;
        
        print_asm_1("ljmp", "", 6, &obj);
    
        operand_read(&obj);
        uint32_t csval=0;
        uint32_t ipval=0;
        memcpy(&ipval,hw_mem+obj.val,4);
        cpu.eip=obj.val;
        memcpy(&csval,hw_mem+obj.val+32,2);  
        cpu.cs.val =csval;

        uint8_t idx=obj.addr&0xf;     
        load_sreg(idx);
        
        


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
