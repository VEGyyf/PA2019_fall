#include "cpu/instr.h"
#include "memory/memory.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	    print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	    operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	    print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	    print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_c2r_l){
int len=1;
	len += modrm_r_rm(eip + 1, &opr_src, &opr_dest);
	opr_dest.data_size=32;
	switch(opr_dest.addr){
		case 0:
			opr_src.val=cpu.cr0.val;
			break;
		case 3:
			opr_src.val=cpu.cr3.val;
			break;
	}
uint8_t idx=(opr_dest.addr&0xf);
        load_sreg(idx);//void load_sreg(uint8_t sreg);
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
        print_asm_2("mov", "", len, &opr_src, &opr_opr_dest);
	return len;
        /*int len = 1;
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        len += modrm_r_rm(eip + 1, &dst, &src);
        src.type=OPR_CREG;
        dst.type=OPR_REG;
        operand_read(&src);
        dst.val=src.val;//?
        uint8_t idx=(dst.addr&0xf);
        load_sreg(idx);//void load_sreg(uint8_t sreg);
        operand_write(&dst);
        print_asm_2("mov", "", len, &src, &dst);
        return len;*/
}
make_instr_func(mov_r2c_l){
int len=1;
	opr_src.data_size=32;
	len += modrm_r_rm(eip + 1, &opr_dest, &opr_src);
	operand_read(&opr_src);
	opr_dest.val=opr_src.val;
	switch(opr_dest.addr){
		case 0:
			cpu.cr0.val=opr_dest.val;
			break;
		case 3:
			cpu.cr3.val=opr_dest.val;
			break;
	}
uint8_t idx=(opr_dest.addr&0xf);
        load_sreg(idx);
 print_asm_2("mov", "", len, &opr_src, &opr_dest);
	return len;
        /*int len = 1;
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        len += modrm_r_rm(eip + 1, &dst, &src);
        src.type=OPR_REG;
        dst.type=OPR_CREG;
        operand_read(&src);
        dst.val=src.val;//?*/
    /*SegDesc tmp;// load 
    uint32_t temp2[2];
    temp2[0]=laddr_read(src.addr,4);
    temp2[1]=laddr_read(src.addr+4,4);
    memcpy(&tmp,temp2,8);*/
        /*uint8_t idx=(dst.addr&0xf);
        load_sreg(idx);//void load_sreg(uint8_t sreg);
        operand_write(&dst);
        print_asm_2("mov", "", len, &src, &dst);
        return len;*/
}
make_instr_func(mov_rm2s_w){
        int len = 1;
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_CS;
        dst.sreg=SREG_CS;
        len += modrm_r_rm(eip + 1, &dst, &src);
        operand_read(&src);
        src.val=src.val&0xff;
        dst.val=src.val;//sign_ext(src.val,16);//?
        uint8_t idx=(dst.addr&0xf);
        load_sreg(idx);//void load_sreg(uint8_t sreg);
        operand_write(&dst);
        print_asm_2("mov", "", len, &src, &dst);
        return len;
}


