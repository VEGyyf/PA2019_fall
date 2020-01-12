#include "cpu/instr.h"

make_instr_func(popa)
{

    if(data_size==16){
    opr_dest.data_size=data_size;
    opr_dest.type=OPR_MEM;//reg?
    opr_dest.addr=cpu.sp;
    opr_dest.sreg=SREG_SS;
	operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.di=opr_dest.val;
	cpu.sp+=data_size/8;//DI ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.si=opr_dest.val;
	cpu.sp+=data_size/8;//SI ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.bp=opr_dest.val;
	cpu.sp+=data_size/8;//BP ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
	cpu.sp+=data_size/8;//throwaway ← Pop (); (* Skip SP *)
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.bx=opr_dest.val;
	cpu.sp+=data_size/8;//BX ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.dx=opr_dest.val;
	cpu.sp+=data_size/8;//DX ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.cx=opr_dest.val;
	cpu.sp+=data_size/8;//CX ← Pop();
    opr_dest.addr=cpu.sp;
    operand_read(&opr_dest);//zhidingdezhandanyuan
    cpu.ax=opr_dest.val;
	cpu.sp+=data_size/8;//AX ← Pop();
    }
    else if(data_size=32){
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
    }
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
