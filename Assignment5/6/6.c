#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct listNode {
    char *name;
    struct listNode *next;
};

const int HashSize = 100;

struct listNode* hashTable[HashSize];

char Name[59][20] = {"jinshan", "linanning", "xujiadong", "cuiwubing", "denghua", "wangsiping", "limengxin", "qiaozhengping", "fanyingxue", "zhangjianwei", "louhongxuan", "weixianzhu", "lijiachen", "zoulinwei", "litingwei", "wujiaxin", "guozijie", "gengziyin", "yujiangyue", "xuxingchen", "wangyue", "bixiaoyu", "zhouyaoxiang", "liumin", "guoyan", "jinenze", "xuechen", "panzhaoyue", "weixiao", "xiaqiuhan", "zhanwenhao", "wujiaxiang", "yeliang", "liyanxuan", "like", "yangqi", "helizhe", "huangbotao", "houmingrong", "gaohao", "dengweihao", "zhangxuefeng", "yangzeyuan", "zhanghongsen", "xiaochangrong", "houbairu", "leichenyong", "wuzijian", "liyifan", "jilincheng", "wangtianyu", "zhuzifei", "liziyue", "shezhucheng", "chenkening", "shengyinuo", "shenyihua", "liyinwen", "linzhenghuan"};

int Hash(char* n) {
    unsigned int hash = 970519;
    while (*n) {
        hash += (hash << 5) + (*n++);
    }
    return (hash & 0x7FFFFFFF) % HashSize;
}

void initHashTable() {
    int collision_times = 0;
    for(int i = 0; i < 59; ++i) {
        int num_hash = Hash(Name[i]);
        if(hashTable[num_hash] == NULL) {
            hashTable[num_hash] = (struct listNode *)malloc(sizeof(struct listNode));
            hashTable[num_hash]->name = Name[i];
            hashTable[num_hash]->next = NULL;

        }
        else {
            ++collision_times;
            struct listNode* p = hashTable[num_hash];
            while(p->next) p = p->next;
            p->next = (struct listNode *)malloc(sizeof(struct listNode));
            p->next->name = Name[i];
            p->next->next = NULL;
        }
    }
    printf("\nHash table size: %d\n", HashSize);
    printf("Collision times: %d\n", collision_times);

    for(int i = 0; i < HashSize; ++i) {
        if(hashTable[i] == NULL) continue;
        struct listNode* p = hashTable[i], *q = hashTable[i];
        while(q) {
            free(q);
            p = p->next;
            q = p;
        }
    }
}

int main(void) {
    for(int i = 0; i < HashSize; ++i) hashTable[i] = NULL;
    printf("Hash function:\n");
    printf("int Hash(char* n) {\n");
    printf("    unsigned int hash = 970519;\n");
    printf("    while (*n) hash += (hash << 5) + (*n++);\n");
    printf("    return (hash & 0x7FFFFFFF) %% HashSize;\n");
    printf("}\n");
    initHashTable();
}
