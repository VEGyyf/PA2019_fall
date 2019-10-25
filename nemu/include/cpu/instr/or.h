#ifndef __INSTR_OR_H__
#define __INSTR_OR_H__

make_instr_impl_2op(or, r, rm, b);
make_instr_impl_2op(or, r, rm, v);
make_instr_impl_2op(or, rm, r, b);
make_instr_impl_2op(or, rm, r, v);
make_instr_impl_2op(or, i, a, b);
make_instr_impl_2op(or, i, a, v);

#endif
