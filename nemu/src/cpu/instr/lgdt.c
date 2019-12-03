


/*ELSE (* instruction = LGDT *)
IF OperandSize = 16
← m16:
THEN GDTR.Limit:Base
24 (* 24 bits of base loaded *)
← m16:
ELSE GDTR.Limit:Base
32;
FI;
FI;*/
