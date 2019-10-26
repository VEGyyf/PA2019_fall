#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__

make_instr_impl_2op(sbb, r, rm, b);
make_instr_impl_2op(sbb, r, rm, v);
make_instr_impl_2op(sbb, rm, r, b);
make_instr_impl_2op(sbb, rm, r, v);
make_instr_impl_2op(sbb, i, a, b);
make_instr_impl_2op(sbb, i, a, v);

#endif
