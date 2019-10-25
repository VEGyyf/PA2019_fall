#ifndef __INSTR_AND_H__
#define __INSTR_AND_H__

make_instr_impl_2op(and, r, rm, b);
make_instr_impl_2op(and, r, rm, v);
make_instr_impl_2op(and, rm, r, b);
make_instr_impl_2op(and, rm, r, v);
make_instr_impl_2op(and, i, a, b);
make_instr_impl_2op(and, i, a, v);

#endif
