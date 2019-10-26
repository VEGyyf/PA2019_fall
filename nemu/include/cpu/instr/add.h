#ifndef __INSTR_ADD_H__
#define __INSTR_ADD_H__

make_instr_func(add, r, rm, b);
make_instr_func(add, r, rm, v);
make_instr_func(add, rm, r, b);
make_instr_func(add, rm, r, v);
make_instr_func(add, i, a, b);
make_instr_func(add, i, a, v);

#endif
