#ifndef __INSTR_JCC_H__
#define __INSTR_JCC_H__

make_instr_func(je_near);
make_instr_func(ja_near);
make_instr_func(jb_near);
make_instr_func(jg_near);
make_instr_func(jl_near);
make_instr_func(jo_near);
make_instr_func(jp_near);
make_instr_func(js_near);
make_instr_func(jae_near);
make_instr_func(jge_near);
make_instr_func(jle_near);
make_instr_func(jna_near);
make_instr_func(jne_near);
make_instr_func(jno_near);
make_instr_func(jnp_near);
make_instr_func(jns_near);
make_instr_func(je_short_);
make_instr_func(ja_short_);
make_instr_func(jb_short_);
make_instr_func(jg_short_);
make_instr_func(jl_short_);
make_instr_func(jo_short_);
make_instr_func(jp_short_);
make_instr_func(js_short_);
make_instr_func(jae_short_);
make_instr_func(jge_short_);
make_instr_func(jle_short_);
make_instr_func(jna_short_);
make_instr_func(jne_short_);
make_instr_func(jno_short_);
make_instr_func(jnp_short_);
make_instr_func(jns_short_);

#endif

/*
#define jcc_helper(suffix) \
	make_instr_impl_1op_cc(j, i, suffix, e) \
	make_instr_impl_1op_cc(j, i, suffix, a) \
	make_instr_impl_1op_cc(j, i, suffix, b) \
	make_instr_impl_1op_cc(j, i, suffix, g) \
	make_instr_impl_1op_cc(j, i, suffix, l) \
	make_instr_impl_1op_cc(j, i, suffix, o) \
	make_instr_impl_1op_cc(j, i, suffix, p) \
	make_instr_impl_1op_cc(j, i, suffix, s) \
	make_instr_impl_1op_cc(j, i, suffix, ae) \
	make_instr_impl_1op_cc(j, i, suffix, ge) \
	make_instr_impl_1op_cc(j, i, suffix, le) \
	make_instr_impl_1op_cc(j, i, suffix, na) \
	make_instr_impl_1op_cc(j, i, suffix, ne) \
	make_instr_impl_1op_cc(j, i, suffix, no) \
	make_instr_impl_1op_cc(j, i, suffix, np) \
	make_instr_impl_1op_cc(j, i, suffix, ns) \

jcc_helper(near)
jcc_helper(short_)
make_instr_impl_1op_cc(j, i, short_, ecxz)
*/
