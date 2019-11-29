#include "memory/cache.h"
#include <stdio.h>

CacheLine cache[1024];

void init_cache(){
    for(int i=0;i<1024;i++){
        cache[i].valid_bit=0;
    }

}
//初始化 cache ，核心就是把 valid bit 都清 0

uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache){
        uint32_t res;
        uint32_t mark_paddr=(0xFFFFE000&paddr);
        mark_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        bool flag=0;//命中与否
        for(uint32_t i=(group<<3);i<8;i++){
            if(cache[i].mark==mark_paddr&&cache[i].valid_bit){//命中
               flag=1;
               if(addrinblock+len-1<64){//不用跨行读写
                    //void* res;
                    void* src=(void*)((&cache[i].data)+addrinblock);
                    memcpy(&res, src, len);
                    //res=(uint32_t)res;
                }
               else{//跨行读写
                    uint32_t part1;
                    uint32_t len1=64-addrinblock;
                    void* src1=(void*)((&cache[i].data)+addrinblock);
                    memcpy(&part1,src1,len1);
                    uint32_t part2;
                    uint32_t len2=len-len1;
                    uint32_t j=i+1;
                    void* src2=(void*)(&cache[j].data);
                    memcpy(&part2,src2,len2);
                    
               }
            }
            
        }
        if(!flag){//不命中，读内存
                
        }

    return res;
}
//读 cache
//根据 paddr 找到标记、组号、与块内地址
//根据组号去定位相应的组（起始 Cache 行号）
//与组内的 CacheLine 比较标记和有效位
//命中怎样？不命中（缺失）又怎样？
//组满了怎办？（随机替换算法)

void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache){
        uint32_t mark_paddr=(0xFFFFE000&paddr);
        mark_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        bool flag=0;//命中与否
        for(uint32_t i=(group<<3);i<8;i++){
            if(cache[i].mark==mark_paddr&&cache[i].valid_bit){//命中
               flag=1;
               if(addrinblock+len-1<64){//不用跨行读写
                    void* res;
                    void* src=(void*)(cache[i].data+addrinblock);
                    memcpy(res, src, len);
                    res=(uint32_t)res;
                }
               else{//跨行读写
                
               }
            }
            
        }
        if(!flag){//不命中，读内存
                
        }
}
//写 cache
//和 cache_read 采用同样过程根据 paddr 定位 CacheLine
//命中怎样？不命中（缺失）又怎样 not write allocate
//写 cache ，同时主存里面对应的块怎么办 write through
