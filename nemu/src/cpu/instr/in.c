#include "cpu/instr.h"
#include "kernel/include/x86/io.h"
#include "device/port_io.h"

make_instr_func(in)
{	
in_byte(uint16_t port){
	uint8_t data;
	asm volatile("in %1, %0"
				 : "=a"(data)
				 : "d"(port));
	return data;
}
}
