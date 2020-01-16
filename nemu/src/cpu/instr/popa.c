#include "cpu/instr.h"

make_instr_func(popa)
{
    cpu.edi=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//EDI ← Pop();
    cpu.esi=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//ESI ← Pop();
    cpu.ebp=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//EBP ← Pop();
	cpu.esp+=data_size/8;//throwaway ← Pop (); (* Skip ESP *)
    cpu.ebx=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//EBX ← Pop();
    cpu.edx=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//EDX ← Pop();
   cpu.ecx=vaddr_read(cpu.esp,SREG_SS, 4);
	cpu.esp+=data_size/8;//ECX ← Pop();
    cpu.eax=vaddr_read(cpu.esp,SREG_SS, 4);
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
