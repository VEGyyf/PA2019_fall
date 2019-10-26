#ifndef __INSTR_SUB_H__
#define __INSTR_SUB_H__

make_instr_func(sub, r, rm, b)
make_instr_func(sub, r, rm, v)
make_instr_func(sub, rm, r, b)
make_instr_func(sub, rm, r, v)
make_instr_func(sub,i,a,b)
make_instr_func(sub,i,a,v)

#endif
