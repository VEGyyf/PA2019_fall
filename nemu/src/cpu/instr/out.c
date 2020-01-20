#include "cpu/instr.h"
//#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(out_b)
{	
        
        uint16_t port=cpu.edx&0xffff;
        pio_write(port, 1, cpu.eax);     
        print_asm_0("out_b", "", 1);
        return 1;
}

make_instr_func(out_v)
{	
        uint16_t port=cpu.edx&0xffff;
        pio_write(port, data_size/8, cpu.eax);     
        print_asm_0("out_v", "", 1);
        return 1;
}
