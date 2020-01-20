#include "cpu/instr.h"
#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(out_b)
{	
        OPERAND src, dst;
        src.data_size = 8;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        src.type=OPR_REG;
        dst.type=OPR_REG;
        operand_read(&src);
        uint16_t port=dst.val;
        out_byte(uint16_t port, uint8_t data)
        operand_write(&dst);
      return 3;
}

make_instr_func(out_v)
{	
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
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
