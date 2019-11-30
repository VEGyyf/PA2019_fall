#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/cache.h"
#include "memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t hw_mem_read(paddr_t paddr, size_t len);
void hw_mem_write(paddr_t paddr, size_t len, uint32_t data);
//CacheLine L1_dcache[1024];

void init_cache(){
    for(int i=0;i<1024;i++){
        L1_dcache[i].valid_bit=0;
    }

}
//初始化 cache ，核心就是把 valid bit 都清 0

uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache){
        uint32_t res=0;
        uint32_t tag_paddr=(0xFFFFE000&paddr);
        tag_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        uint32_t index=(group<<3);
        uint8_t alldata[128];//待读取的一/两整行
        bool shot=false;//命中与否
        int  line=0;//组内第几行

        /*for(int i=0;i<8;i++){
            if(cache[index+i].tag==tag_paddr&&cache[index+i].valid_bit==1){//命中
               shot=true;
               line=i;
               break;
                }
               
            }*/
            
        
        if(!shot){//不命中，读内存
               int ptr=0;
               for(;ptr<8;ptr++){
                    if(!cache[ptr].valid_bit){//找到空闲行
                        line=ptr;
                        break;
                    }
                } 
                if(ptr==8){//组满随机替换
                    line=rand()%8;                  
                }  
                cache[index+line].valid_bit=1;
                cache[index+line].tag=tag_paddr;
                memcpy(&cache[index+line].data,hw_mem+paddr-addrinblock,64);//把主存块搬到cache
        }
        memcpy(alldata,&cache[index+line].data,64);
        if(addrinblock+len>64)*(uint32_t*)(alldata+64)=cache_read(paddr-addrinblock+64,64,cache);//跨行
        memcpy(&res,alldata+addrinblock,len);
    return res;
}
//读 cache
//根据 paddr 找到标记、组号、与块内地址
//根据组号去定位相应的组（起始 Cache 行号）
//与组内的 CacheLine 比较标记和有效位
//命中怎样？不命中（缺失）又怎样？
//组满了怎办？（随机替换算法)

void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache){
        uint32_t tag_paddr=(0xFFFFE000&paddr);
        tag_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        uint32_t index=(group<<3);
        //uint8_t alldata[128];//待写入的一/两整行
        bool shot=0;//命中与否
        int  line=0;//组内第几行
      
        for(int i=0;i<8;i++){
            if(cache[index+i].tag==tag_paddr&&cache[index+i].valid_bit){//命中
               shot=1;
               line=i;
               break;
                }
               
            }
            
        
        if(shot){//命中,write through
           
               if(addrinblock+len>64){//跨行
                    uint32_t len1=64-len;
                    memcpy(&cache[index+line].data+addrinblock,&data,len1);
                    uint32_t len2=len-len1;
                    memcpy(&cache[index+line+1].data,&data+len1,len2);
                }
                else{
                     memcpy(&cache[index+line].data+addrinblock,&data,len);
                }

        }
        memcpy(hw_mem+paddr-addrinblock,&data,len);//写主存
        //memcpy(alldata,cache[index+line].data,64);
        
        

}
//写 cache
//和 cache_read 采用同样过程根据 paddr 定位 CacheLine
//命中怎样？不命中（缺失）又怎样 not write allocate
//写 cache ，同时主存里面对应的块怎么办 write through
