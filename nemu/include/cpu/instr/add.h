#ifndef __INSTR_ADD_H__
#define __INSTR_ADD_H__

make_instr_impl_2op(add, r, rm, b);
make_instr_impl_2op(add, r, rm, v);
make_instr_impl_2op(add, rm, r, b);
make_instr_impl_2op(add, rm, r, v);
make_instr_impl_2op(add, i, a, b);
make_instr_impl_2op(add, i, a, v);

#endif
