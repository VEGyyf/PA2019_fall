#include "cpu/instr.h"

make_instr_func(pusha)
{
	if(data_size==16){
        
                    
            
    }
    else if(data_size==32){
    uint32_t temp=cpu.esp;//Temp ← (ESP);
	cpu.esp-=data_size/8;
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
    opr_dest.val=cpu.eax;
    operand_write(&opr_dest);//Push(EAX);

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
