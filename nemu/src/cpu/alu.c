#include "cpu/cpu.h"
// CF contains information relevant to unsigned integers 
void set_CF_add(uint32_t result, uint32_t src, size_t data_size) { 
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    cpu.eflags.CF = result < src; 
}
void set_ZF(uint32_t result, size_t data_size) { 
    result = result & (0xFFFFFFFF >> (32 - data_size)); 
    cpu.eflags.ZF = (result == 0); 
}
// SF and OF contain information relevant to signed integers 
void set_SF(uint32_t result, size_t data_size) { 
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    cpu.eflags.SF = sign(result); 
}
void set_PF(uint32_t result) { // 简单暴力穷举也行
    result = sign_ext(result & 0xFF, 8); //保留低八位，符号拓展
	uint32_t sum=0;
    for(uint32_t i=1;i<256;i<<=1){
        		if(result & i)sum++;

    }
    if(sum==0||sum==2||sum==4||sum==6||sum==8)
        cpu.eflags.PF=1;
    else
        cpu.eflags.PF=0;
    
}
void set_OF_add(uint32_t result, uint32_t src, uint32_t dest, size_t data_size){
    switch(data_size) { 
        case 8: 
            result = sign_ext(result & 0xFF, 8); 
            src = sign_ext(src & 0xFF, 8); 
            dest = sign_ext(dest & 0xFF, 8); 
            break; 
        case 16: 
            result = sign_ext(result & 0xFFFF, 16); 
            src = sign_ext(src & 0xFFFF, 16);   
            dest = sign_ext(dest & 0xFFFF, 16); 
            break; 
            default: break;// do nothing 
    } 
    if(sign(src) == sign(dest)) { 
               if(sign(src) != sign(result)) 
                            cpu.eflags.OF = 1; 
               else 
                            cpu.eflags.OF = 0;
    } else { 
               cpu.eflags.OF = 0; 
            }
 }
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res = 0; 
    res = dest + src;

    set_CF_add(res, src, data_size); 
    set_PF(res); 
    // set_AF();  我们不模拟AF 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
    set_OF_add(res, src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
}
void set_CF_adc(uint32_t result, uint32_t src, size_t data_size) { 
    uint32_t src_b=src;
    src+=cpu.eflags.CF;
    result = sign_ext(result & (0xFFFFFFFF>> (32 - data_size)), data_size); 
    src = sign_ext(src & (0xFFFFFFFF>> (32 - data_size)), data_size); 
    src_b = sign_ext(src_b & (0xFFFFFFFF>> (32 - data_size)), data_size); 
    if(src_b>src){cpu.eflags.CF = 1;return;}//judge whether src+flag overflow.CAUTION!If so,return right away!
    cpu.eflags.CF = result < src; 
 }
void set_OF_adc(uint32_t result, uint32_t src, uint32_t dest, size_t data_size){
    switch(data_size) { 
        case 8: 
            result = sign_ext(result & 0xFF, 8); 
            src = sign_ext(src & 0xFF, 8); 
            dest = sign_ext(dest & 0xFF, 8); 
            break; 
        case 16: 
            result = sign_ext(result & 0xFFFF, 16); 
            src = sign_ext(src & 0xFFFF, 16);   
            dest = sign_ext(dest & 0xFFFF, 16); 
            break; 
            default: break;// do nothing 
    } 
    if(sign(src) == sign(dest)) { 
               if(sign(src) != sign(result)) 
                            cpu.eflags.OF = 1; 
               else 
                            cpu.eflags.OF = 0;
    } else { 
               cpu.eflags.OF = 0; 
            }
 }
uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res = 0; 
    res = dest + src+cpu.eflags.CF;
    //res-=cpu.eflags.CF;
    set_CF_adc(res, src, data_size); 
    //res+=cpu.eflags.CF;
    set_PF(res); 
    // set_AF();  我们不模拟AF 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
    set_OF_adc(res, src, dest, data_size);
 
    return res & (0xFFFFFFFF >> (32 - data_size));
}
void set_CF_sub(uint32_t dest, uint32_t src, size_t data_size) { 
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    cpu.eflags.CF = dest<src; 
}
void set_OF_sub( uint32_t res, uint32_t src, uint32_t dest, size_t data_size){

    switch(data_size) { 
        case 8: 
            res= sign_ext(res & 0xFF, 8); 
            src = sign_ext(src & 0xFF, 8); 
            dest = sign_ext(dest & 0xFF, 8); 
            break; 
        case 16: 
            res= sign_ext(res & 0xFFFF, 16); 
            src = sign_ext(src & 0xFFFF, 16);   
            dest = sign_ext(dest & 0xFFFF, 16); 
            break; 
            default: break;// do nothing 
    } 
    if(sign(src) != sign(dest)) { 
               if(sign(src) == sign(res) )
                            cpu.eflags.OF = 1; 
               else 
                            cpu.eflags.OF = 0;
    } else { 
               cpu.eflags.OF = 0; 
            }
 }
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res = 0; 
    res = dest - src;

    set_CF_sub(dest, src, data_size); 
    set_PF(res); 
    // set_AF();  我们不模拟AF 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
    set_OF_sub(res,src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
}
void set_CF_sbb(uint32_t dest, uint32_t src, size_t data_size) { 
    uint32_t src_b=src;
    src+=cpu.eflags.CF;
    dest = sign_ext(dest& (0xFFFFFFFF>> (32 - data_size)), data_size); 
    src = sign_ext(src & (0xFFFFFFFF>> (32 - data_size)), data_size); 
    src_b = sign_ext(src_b & (0xFFFFFFFF>> (32 - data_size)), data_size); 
    if(src_b>src){cpu.eflags.CF = 1;return;}//judge whether src+flag overflow.CAUTION!If so,return right away!
    cpu.eflags.CF = dest < src; 
}

void set_OF_sbb( uint32_t res, uint32_t src, uint32_t dest, size_t data_size){

    switch(data_size) { 
        case 8: 
            res= sign_ext(res & 0xFF, 8); 
            src = sign_ext(src & 0xFF, 8); 
            dest = sign_ext(dest & 0xFF, 8); 
            break; 
        case 16: 
            res= sign_ext(res & 0xFFFF, 16); 
            src = sign_ext(src & 0xFFFF, 16);   
            dest = sign_ext(dest & 0xFFFF, 16); 
            break; 
            default: break;// do nothing 
    } 
    if(sign(src) != sign(dest)) { 
               if(sign(src) == sign(res) )
                            cpu.eflags.OF = 1; 
               else 
                            cpu.eflags.OF = 0;
    } else { 
               cpu.eflags.OF = 0; 
            }
 }
uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res = 0; 
    res = dest - src-cpu.eflags.CF;

    set_CF_sbb(dest, src, data_size); 
    set_PF(res); 
    // set_AF();  我们不模拟AF 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
    set_OF_sbb(res,src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
    uint32_t res=0;
    res=dest&src;
    cpu.eflags.OF=0;
    cpu.eflags.CF=0;
    set_PF(res); 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
   	return res & (0xFFFFFFFF >> (32 - data_size));
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
void set_CF_shl(uint32_t dest, uint32_t src, size_t data_size) { 
     uint32_t count=1;
    for(uint32_t i=0;i<data_size-src;i++)//count = 第data_size-src位（即移出到CF那一位）为1，其余为0
        count<<=1;
    uint32_t judge=dest&count;
    judge>>=data_size-src;    //save the data_size-src th bit
     cpu.eflags.CF = judge; 
}
uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res=0;
	res=dest<<src;
    set_CF_shl(dest, src, data_size); //CAUTION:parqameter--dest
    set_PF(res); 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
   	return res & (0xFFFFFFFF >> (32 - data_size));
}
void set_CF_shr(uint32_t dest, uint32_t src, size_t data_size) { 
    uint32_t flag=1;
    for(uint32_t i=0;i<src-1;i++)//count = 第src位（即移出到CF那一位）为1，其余为0
        flag<<=1;
    uint32_t judge=dest&flag;
    judge>>=src-1; 
    cpu.eflags.CF = judge; 
}
uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res=0;
    dest = dest & (0xFFFFFFFF >> (32 - data_size)); 
    src  = src &(0xFFFFFFFF >> (32 - data_size)); //高位补0
    res=dest>>src;
    set_CF_shr(dest, src, data_size); 
    set_PF(res); 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
    return res & (0xFFFFFFFF >> (32 - data_size));
}
void set_CF_sar(uint32_t dest, uint32_t src, size_t data_size) { 
    int32_t flag=1;
    for(uint32_t i=0;i<src-1;i++)//count = 第src位（即移出到CF那一位）为1，其余为0
        flag<<=1;
    uint32_t judge=dest&flag;
    judge>>=src-1; 
    cpu.eflags.CF = judge; 
}
uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    int32_t dest_sign = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    src = src & (0xFFFFFFFF >> (32 - data_size)); 
    int32_t res=dest_sign>>src;
    //res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size); 
    set_CF_sar(dest, src, data_size); 
    set_PF(res); 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
   	return res & (0xFFFFFFFF >> (32 - data_size));
}


void set_CF_sal(uint32_t dest, uint32_t src, size_t data_size) { //SHL/SAL一样:逻辑/算术左移,最高位进到CF，最低位补0;
    uint32_t count=1;
    for(uint32_t i=0;i<data_size-src;i++)//count = 第data_size-src位（即移出到CF那一位）为1，其余为0
        count<<=1;
    uint32_t judge=dest&count;
    judge>>=data_size-src;    //save the data_size-src th bit
     cpu.eflags.CF = judge; 
}
uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)//pass
{
    uint32_t res=0;
	res=dest<<src;
    set_CF_sal(dest, src, data_size); 
    set_PF(res); 
    set_ZF(res, data_size);    
    set_SF(res, data_size); 
   	return res & (0xFFFFFFFF >> (32 - data_size));

}
