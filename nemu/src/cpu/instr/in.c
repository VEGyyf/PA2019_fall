#include "cpu/instr.h"
//#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(in_b)
{	
       	operand_read(&opr_src);
    uint16_t port=src.val;
	opr_dest.val = pio_read(port, 1);
	operand_write(&opr_dest);/* OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        src.type=OPR_REG;
        dst.type=OPR_REG;
        operand_read(&src);
        uint16_t port=src.val;
        dst.val=pio_read(port, 1);
        operand_write(&dst);*/
        print_asm_2("in", "_b", 3, &opr_src, &opr_dst);
      return 3;
}

make_instr_func(in_v)
{	    	operand_read(&opr_src);
    uint16_t port=src.val;
	opr_dest.val = pio_read(port, data_size/8);
	operand_write(&opr_dest);/*OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        src.type=OPR_REG;
        dst.type=OPR_REG;
        operand_read(&src);
        uint16_t port=src.val;
        //if(data_size==16)dst.val=in_word(port);
       // else if(data_size==32)dst.val=in_long(port);
        dst.val=pio_read(port, data_size/8);
        operand_write(&dst);*/
        print_asm_2("in", "_v", 3, &src, &dst);
      return 3;
}
