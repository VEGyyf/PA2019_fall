#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(call_near)
{
    OPERAND rel;
	//printf("At %x ,",cpu.eip);
	cpu.esp-=4;
	//printf("call begin\n");
	vaddr_write(cpu.esp,SREG_SS,4,eip+data_size/8+1);
	//printf("eip b4 call is %x\n",cpu.eip);
	//uint32_t ret=vaddr_read(cpu.esp,SREG_SS,4);
	//printf("addr is %x\n",ret);
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;
	operand_read(&rel);
	/*if(data_size==16){
		eip+=vaddr_read(eip+1, SREG_CS, 2)+3;
	}
	else{// data_size==32
		eip+=vaddr_read(eip+1,SREG_CS,4)+5;
	}*/
	print_asm_1("call", "", 1, &rel);
	cpu.eip+=rel.val+data_size/8+1;
	//printf("calling to %x,esp is %x\n",cpu.eip,cpu.esp);
	return 0;
/*cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,data_size/8,cpu.eip);//push eip


        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;//=jmp,跳转到指定地址*/
}

make_instr_func(call_near_indirect)
{
	int len=1;
	OPERAND rel;
	cpu.esp-=4;
	len+=modrm_rm(eip + 1, &rel);
    rel.data_size = data_size;
	operand_read(&rel);
	/*if(data_size==16){
		eip+=vaddr_read(eip+1, SREG_CS, 2)+3;
	}
	else{// data_size==32
		eip+=vaddr_read(eip+1,SREG_CS,4)+5;
	}*/
	print_asm_1("call", "", 1, &rel);
	vaddr_write(cpu.esp,SREG_SS,4,eip+len);
	cpu.eip=rel.val;
	return 0;   
/*cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,data_size/8,cpu.eip);//Push(EIP);

        OPERAND obj;
        obj.sreg = SREG_SS;
        obj.data_size = data_size;
        obj.addr=eip+1;
        obj.type=OPR_MEM;
        operand_read(&obj);
        cpu.eip =obj.val;
      
        //int offset = sign_ext(rel.val, data_size);
        print_asm_1("call", "", 1 + data_size / 8, &obj);

       

        return 0;//=jmp,跳转到指定地址*/
}


