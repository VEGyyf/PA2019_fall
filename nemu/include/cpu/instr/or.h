#ifndef __INSTR_OR_H__
#define __INSTR_OR_H__

make_instr_func(or, r, rm, b);
make_instr_func(or, r, rm, v);
make_instr_func(or, rm, r, b);
make_instr_func(or, rm, r, v);
make_instr_func(or, i, a, b);
make_instr_func(or, i, a, v);

#endif
