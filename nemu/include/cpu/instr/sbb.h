#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__

make_instr_impl_2op(abb, r, rm, b);
make_instr_impl_2op(abb, r, rm, v);
make_instr_impl_2op(abb, rm, r, b);
make_instr_impl_2op(abb, rm, r, v);
make_instr_impl_2op(abb, i, a, b);
make_instr_impl_2op(abb, i, a, v);

#endif
