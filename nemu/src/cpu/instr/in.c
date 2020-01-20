#include "cpu/instr.h"
//#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(in_b)
{	    
        uint16_t port=cpu.edx&0xffff;
        cpu.eax=pio_read(port, 1);      
        print_asm_0("in_b", "", 1);
        return 1;
}

make_instr_func(in_v)
{	    uint16_t port=cpu.edx&0xffff;
        cpu.eax=pio_read(port, data_size/8);      
        print_asm_0("in_v", "", 1);
        return 1;
}
