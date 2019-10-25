#ifndef __INSTR_XOR_H__
#define __INSTR_XOR_H__

make_instr_impl_2op(xor, r, rm, b)
make_instr_impl_2op(xor, r, rm, v)
make_instr_impl_2op(xor, rm, r, b)
make_instr_impl_2op(xor, rm, r, v)
make_instr_impl_2op(xor,i,a,b)
make_instr_impl_2op(xor,i,a,v)

#endif
