#include "cpu/instr.h"

make_instr_func(iret)
{
    
    print_asm_0("iret", "", 1);
    return 1 ;
}
/*
当使用IRET指令返回到相同保护级别的任务时，IRET会从堆栈弹出代码段选择子及指令指针分别到CS与IP寄存器，并弹出标志寄存器内容到EFLAGS寄存器。
?16?32?va?pa?pe?
*/
