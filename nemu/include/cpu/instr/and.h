#ifndef __INSTR_AND_H__
#define __INSTR_AND_H__

make_instr_func(and, r, rm, b);
make_instr_func(and, r, rm, v);
make_instr_func(and, rm, r, b);
make_instr_func(and, rm, r, v);
make_instr_func(and, i, a, b);
make_instr_func(and, i, a, v);

#endif
