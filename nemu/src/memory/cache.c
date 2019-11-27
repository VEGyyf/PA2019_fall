void init_cache();
//初始化 cache ，核心就是把 valid bit 都清 0

uint32_t cache_read paddr_t paddr , size_t len , CacheLine *cache);
//读 cache
//根据 paddr 找到标记、组号、与块内地址
//根据组号去定位相应的组（起始 Cache 行号）
//与组内的 CacheLine 比较标记和有效位
//命中怎样？不命中（缺失）又怎样？
//组满了怎办？（ 随机替换算法)

void cache_write paddr_t paddr , size_t len , uint32_t data, CacheLine *cache);
//写 cache
//和 cache_read 采用同样过程根据 paddr 定位 CacheLine
//命中怎样？不命中（缺失）又怎样 not write allocate
//写 cache ，同时主存里面对应的块怎么办 write through
