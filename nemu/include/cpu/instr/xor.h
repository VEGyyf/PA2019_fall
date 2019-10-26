#ifndef __INSTR_XOR_H__
#define __INSTR_XOR_H__

make_instr_func(xor, r, rm, b)
make_instr_func(xor, r, rm, v)
make_instr_func(xor, rm, r, b)
make_instr_func(xor, rm, r, v)
make_instr_func(xor,i,a,b)
make_instr_func(xor,i,a,v)

#endif
