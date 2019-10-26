#ifndef __INSTR_SUB_H__
#define __INSTR_SUB_H__

make_instr_impl_2op(sub, r, rm, b)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, rm, r, b)
make_instr_impl_2op(sub, rm, r, v)
make_instr_impl_2op(sub,i,a,b)
make_instr_impl_2op(sub,i,a,v)

#endif
