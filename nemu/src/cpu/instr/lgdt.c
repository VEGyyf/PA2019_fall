#include "cpu/instr.h"

make_instr_func(lgdt)
{
        
}


/*ELSE (* instruction = LGDT *)
IF OperandSize = 16

THEN GDTR.Limit:Base    ← m16:24 (* 24 bits of base loaded *)

ELSE GDTR.Limit:Base    ← m16:32;
FI;
FI;*/
