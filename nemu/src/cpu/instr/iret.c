#include "cpu/instr.h"

make_instr_func(iret)
{
    
    print_asm_0("iret", "", 1);
    return 0 ;
}
/*
通过iret 指令恢复最初被保护的程序断点和状态信息，返回原程序被中断的指令（或下一条，根据保护断点时具体保存的EIP 决定）继续执行。
eip<--pop()
cs<--pop()
eflags<--pop()

?16?32?va?pa?pe?
*/
