typedef struct{
       uint8_t valid_bit;
       uint32_t tag;
       uint8_t data[64];

}CacheLine;
CacheLine L1_dcache[1024];
void init_cache();//初始化 cache ，核心就是把 valid bit 都清 0

uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache);//读 cache
//前两个参数分别是物理地址和读的字节数
//最后一个参数就是 cache 数组的首地址，假设在 cache.h 中定义的 Cache 行的结构体名称为 CacheLine
//返回值为读出的数据
void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache);//写 cache
//除 data 参数是待写的数据外，其它参数含义和 cache_read 相同
//不需要返回值

