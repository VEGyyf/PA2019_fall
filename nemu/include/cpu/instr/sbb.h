#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__

make_instr_func(sbb, r, rm, b);
make_instr_func(sbb, r, rm, v);
make_instr_func(sbb, rm, r, b);
make_instr_func(sbb, rm, r, v);
make_instr_func(sbb, i, a, b);
make_instr_func(sbb, i, a, v);

#endif
