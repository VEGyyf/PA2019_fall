#include "cpu/instr.h"

make_instr_func(pusha)
{
	operand_read(&opr_src);
   
	if(opr_src->data_size==16){
        
                    
            
    }
    else if(opr_src->data_size==32){
         uint32_t temp=cpu.esp;
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
