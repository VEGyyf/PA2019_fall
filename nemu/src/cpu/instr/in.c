#include "cpu/instr.h"
#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(in_b)
{	
    in_byte(uint16_t port)
}

make_instr_func(in_v)
{	
    in_byte(uint16_t port)
}
