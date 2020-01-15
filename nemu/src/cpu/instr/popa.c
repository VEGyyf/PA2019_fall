#include "cpu/instr.h"

make_instr_func(popa)
{
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;//reg?
    opr_dest.addr=cpu.esp;
    opr_dest.sreg=SREG_SS;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.edi=opr_dest.val;
	cpu.esp+=data_size/8;//EDI ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.esi=opr_dest.val;
	cpu.esp+=data_size/8;//ESI ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.ebp=opr_dest.val;
	cpu.esp+=data_size/8;//EBP ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
	cpu.esp+=data_size/8;//throwaway ← Pop (); (* Skip ESP *)
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.ebx=opr_dest.val;
	cpu.esp+=data_size/8;//EBX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.edx=opr_dest.val;
	cpu.esp+=data_size/8;//EDX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.ecx=opr_dest.val;
	cpu.esp+=data_size/8;//ECX ← Pop();
    opr_dest.addr=cpu.esp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.eax=opr_dest.val;
	cpu.esp+=data_size/8;//EAX ← Pop();
    print_asm_0("popa", "", 1);
    return 1 ;
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
