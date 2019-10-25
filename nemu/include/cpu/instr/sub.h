#ifndef __INSTR_SUB_H__
#define __INSTR_SUB_H__

make_instr_impl_2op(adc, r, rm, b)
make_instr_impl_2op(adc, r, rm, v)
make_instr_impl_2op(adc, rm, r, b)
make_instr_impl_2op(adc, rm, r, v)
make_instr_impl_2op(adc,i,a,b)
make_instr_impl_2op(adc,i,a,v)

#endif
