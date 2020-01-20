#include "cpu/instr.h"
#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(in_b)
{	
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = 8;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        src.type=OPR_REG;
        dst.type=OPR_REG;
        operand_read(&src);
        uint16_t port=src.val;
        dst.val=in_byte(port);
        operand_write(&dst);
      return 3;
}

make_instr_func(in_v)
{	
    in_byte(uint16_t port)
}
