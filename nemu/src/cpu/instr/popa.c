#include "cpu/instr.h"

make_instr_func(popa)
{

    if(data_size==16){

    }
    else if(data_size=32){
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.edi=opr_dest.val;
	cpu.esp+=data_size/8;
/
    uint8_t len=1;
    opr_dest.data_size=data_size;//!!initialize
    opr_dest.type=OPR_MEM;
    opr_dest.addr=cpu.esp;
	operand_read(&opr_dest);//zhidingdezhandanyuan

    cpu.eip=opr_dest.val;
    cpu.esp+=data_size/8;
    }
    return 0 ;//the length of opr=0
}
/*IF OperandSize = 16 (* instruction = POPA *)
THEN
DI ← Pop();
SI ← Pop();
BP ← Pop();
throwaway ← Pop (); (* Skip SP *)
BX ← Pop();
DX ← Pop();
CX ← Pop();
AX ← Pop();
ELSE (* OperandSize = 32, instruction = POPAD *)
EDI ← Pop();
ESI ← Pop();
EBP ← Pop();
throwaway ← Pop (); (* Skip ESP *)
EBX ← Pop();
EDX ← Pop();
ECX ← Pop();
EAX ← Pop();
FI;
*/
