#include "cpu/instr.h"

make_instr_func(cld)
{
    cpu.eflags.DF=0;
    return 1;
}
