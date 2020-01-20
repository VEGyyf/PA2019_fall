#include "cpu/instr.h"
//#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(out_b)
{	
        OPERAND src, dst;
        src.data_size = data_size;
        dst.data_size = data_size;
        src.sreg=SREG_SS;
        dst.sreg=SREG_SS;
        src.type=OPR_REG;
        dst.type=OPR_REG;
        operand_read(&src);
        operand_read(&dst);
        uint32_t data=src.val;
        uint16_t port=dst.val;
        pio_write(port, 1, data);
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
        operand_read(&dst);
        uint16_t port=dst.val;
        uint32_t data=src.val;
        /*if(data_size==16){
        uint16_t data=src.val;
        out_byte(port, data);
        }
        else if(data_size==32){
        uint32_t data=src.val;
        out_byte(port, data);
        }*/
        pio_write(port, data_size/8, data);
        return 3;
}
