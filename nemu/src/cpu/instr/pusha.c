#include "cpu/instr.h"

make_instr_func(pusha)
{
	if(data_size==16){
    uint16_t temp=cpu.esp;//Temp ← (ESP);
	cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_REG;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_SS;
    opr_dest.val=cpu.ax;
    operand_write(&opr_dest);//Push(EAX);
    opr_dest.val=cpu.cx;
    operand_write(&opr_dest);//Push(ECX);
    opr_dest.val=cpu.dx;
    operand_write(&opr_dest);//Push(EDX);
    opr_dest.val=cpu.bx;
    operand_write(&opr_dest);//Push(EBX);
    opr_dest.val=cpu.temp;
    operand_write(&opr_dest);//Push(Temp);
    opr_dest.val=cpu.bp;
    operand_write(&opr_dest);//Push(EBP);
    opr_dest.val=cpu.si;
    operand_write(&opr_dest);//Push(ESI);
    opr_dest.val=cpu.di;
    operand_write(&opr_dest);//Push(EDI);       
    }
    else if(data_size==32){
    uint32_t temp=cpu.esp;//Temp ← (ESP);
	cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_REG;
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_SS;
    opr_dest.val=cpu.eax;
    operand_write(&opr_dest);//Push(EAX);
    opr_dest.val=cpu.ecx;
    operand_write(&opr_dest);//Push(ECX);
    opr_dest.val=cpu.edx;
    operand_write(&opr_dest);//Push(EDX);
    opr_dest.val=cpu.ebx;
    operand_write(&opr_dest);//Push(EBX);
    opr_dest.val=cpu.temp;
    operand_write(&opr_dest);//Push(Temp);
    opr_dest.val=cpu.ebp;
    operand_write(&opr_dest);//Push(EBP);
    opr_dest.val=cpu.esi;
    operand_write(&opr_dest);//Push(ESI);
    opr_dest.val=cpu.edi;
    operand_write(&opr_dest);//Push(EDI);
    }

    
}
/*IF OperandSize = 16 (* PUSHA instruction *)
THEN
Temp ← (SP);
Push(AX);
Push(CX);
Push(DX);
Push(BX);
Push(Temp);
Push(BP);
Push(SI);
Push(DI);
ELSE (* OperandSize = 32, PUSHAD instruction *)
Temp ← (ESP);
Push(EAX);
Push(ECX);
Push(EDX);
Push(EBX);
Push(Temp);
Push(EBP);
Push(ESI);
Push(EDI);
FI;
*/
