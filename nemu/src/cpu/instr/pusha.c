#include "cpu/instr.h"

make_instr_func(pusha)
{

    uint32_t temp=cpu.esp;//Temp ← (ESP);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.eax);//Push(EAX);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.ecx);//Push(ECX);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.edx);//Push(EDX);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.ebx);//Push(EBX);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,temp);//Push(Temp);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.ebp);//Push(EBP);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.esi);//Push(ESI);
	cpu.esp-=data_size/8;
    vaddr_write(cpu.esp,SREG_SS,4,cpu.edi);//Push(EDI);
    print_asm_0("pusha", "", 1);
    return 1;
    
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
