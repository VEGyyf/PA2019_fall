#include "cpu/instr.h"

make_instr_func(int_)
{   uint8_t intr_no=0x80;
	raise_intr(intr_no);
    return 1;//?
}

/*
到系统执行到int $0x80 自陷指令后，即获取intr_no = 0x80 并执行raise_sw_intr()。
*/
/*IF PE = 0
THEN GOTO REAL-ADDRESS-MODE;
ELSE GOTO PROTECTED-MODE;
FI;
REAL-ADDRESS-MODE:
Push (FLAGS);
IF ← 0; (* Clear interrupt flag *)
TF ← 0; (* Clear trap flag *)
Push(CS);
Push(IP);
(* No error codes are pushed *)
CS ← IDT[Interrupt number * 4].selector;
IP ← IDT[Interrupt number * 4].offset;
PROTECTED-MODE:
Interrupt vector must be within IDT table limits,
else #GP(vector number * 8+2+EXT);
Descriptor AR byte must indicate interrupt gate, trap gate, or task gate,
else #GP(vector number * 8+2+EXT);
IF software interrupt (* i.e. caused by INT n, INT 3, or INTO *)
THEN
IF gate descriptor DPL < CPL
THEN #GP(vector number * 8+2+EXT);
FI;
FI;
Gate must be present, else #NP(vector number * 8+2+EXT);
IF trap gate OR interrupt gate
THEN GOTO TRAP-GATE-OR-INTERRUPT-GATE;
ELSE GOTO TASK-GATE;
FI;*/
