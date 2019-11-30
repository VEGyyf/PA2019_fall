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
        /*uint32_t res=0;
        uint32_t tag_paddr=(0xFFFFE000&paddr);
        tag_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        uint32_t index=(group<<3);
        uint8_t alldata[128];//待读取的一/两整行
        bool shot=false;//命中与否
        int  line=0;//组内第几行

        for(int i=0;i<8;i++){
            if(cache[index+i].tag==tag_paddr&&cache[index+i].valid_bit==1){//命中
               shot=true;
               line=i;
               break;
                }
               
            }
            
        
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
    return res;*/
    uint32_t res=0;
    uint32_t tag_paddr=(0xFFFFE000&paddr);
        tag_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        bool shot=0;//命中与否
        //bool full=1;//是否组满
        for(uint32_t i=(group<<3);i<((group+1)<<3);i++){
            if(cache[i].tag==tag_paddr&&cache[i].valid_bit){//命中
               shot=1;
               if(addrinblock+len-1<64){//不用跨行读写
      
                    memcpy(&res,&cache[i].data+addrinblock,len);
                   
                }
               else{//跨行读写
                    uint32_t part1=0;
                    uint32_t len1=64-addrinblock;
                    //void* src1=(void*)((&cache[i].data)+addrinblock);
                    memcpy(&part1,(&cache[i].data)+addrinblock,len1);
                    uint32_t part2=0;
                    uint32_t len2=len-len1;
                    uint32_t j=i+1;
                    //void* src2=(void*)(&cache[j].data);
                    memcpy(&part2,&cache[j].data,len2);
                    part2<<=len1;
                    res=part2|part1;
               }
            }
            
        }
        if(!shot){//不命中，非写分配法
               
               uint32_t ptr=(group<<3);
               for(;ptr<8;ptr++){
                    if(!cache[ptr].valid_bit)//找到空闲行
                        break;
                } 
                if(ptr==8)//组满随机替换
                    ptr =rand()%8;
            cache[ptr].data=hw_mem_read(paddr,len);
            cache[ptr].valid_bit=1;
            cache[ptr].tag=tag_paddr;
            res=cache_read (paddr , len , cache);   
    return res;
        
/*uint32_t res=0;
        uint32_t tag_paddr=(0xFFFFE000&paddr);
        tag_paddr>>=13;
        uint32_t group=(0x00001FC0&paddr);
        group>>=6;
        uint32_t addrinblock=(0x0000003F&paddr);
        bool shot=0;//命中与否
        //bool full=1;//是否组满
        for(uint32_t i=(group<<3);i<8;i++){
            if(cache[i].tag==tag_paddr&&cache[i].valid_bit){//命中
               shot=1;
               if(addrinblock+len-1<64){//不用跨行读写
                  
                    //void* src=(void*)((&cache[i].data)+addrinblock);
                    memcpy(&res, (&cache[i].data)+addrinblock, len);
                   
                }
               else{//跨行读写
                    uint32_t part1=0;
                    uint32_t len1=64-addrinblock;
                    //void* src1=(void*)((&cache[i].data)+addrinblock);
                    memcpy(&part1,(&cache[i].data)+addrinblock,len1);
                    uint32_t part2=0;
                    uint32_t len2=len-len1;
                    uint32_t j=i+1;
                    //void* src2=(void*)(&cache[j].data);
                    memcpy(&part2,&cache[j].data,len2);
                    part2<<=len2;
                    res=part2|part1;
               }
            }
            
        }
        if(!shot){//不命中，读内存
               uint32_t ptr=(group<<3);
               for(;ptr<8;ptr++){
                    if(!cache[ptr].valid_bit){//找到空闲行

                    
                        break;
                    }
                } 
                if(ptr==8){//组满随机替换
                    ptr =rand()%8;

                       
                }  
                    cache[ptr].data=hw_mem_read(paddr,len);
                        cache[ptr].valid_bit=1;
                        cache[ptr].tag=tag_paddr;
            res=cache_read (paddr , len , cache);             
        }


    return res;*/

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
        bool shot=0;//命中与否
        //bool full=1;//是否组满
        for(uint32_t i=(group<<3);i<((group+1)<<3);i++){
            if(cache[i].tag==tag_paddr&&cache[i].valid_bit){//命中
               shot=1;
               if(addrinblock+len-1<64){//不用跨行读写
      
                    memcpy(&cache[i].data, &data, len);
                    hw_mem_write(paddr, len, data);
                   
                }
               else{//跨行读写
                    
                    uint32_t len1=64-addrinblock;
                    //void* src1=(void*)((&cache[i].data)+addrinblock);
                    memcpy((&cache[i].data)+addrinblock,&data,len1);
                    
                    uint32_t len2=len-len1;
                    uint32_t j=i+1;
                    //void* src2=(void*)(&cache[j].data);
                    memcpy(&cache[j].data,&data+len1,len2);
                   
                    hw_mem_write(paddr, len, data);
               }
            }
            
        }
        if(!shot){//不命中，非写分配法
               
                  hw_mem_write(paddr, len, data);       
        }
        
        
        

}
//写 cache
//和 cache_read 采用同样过程根据 paddr 定位 CacheLine
//命中怎样？不命中（缺失）又怎样 not write allocate
//写 cache ，同时主存里面对应的块怎么办 write through
