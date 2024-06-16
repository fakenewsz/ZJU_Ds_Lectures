//移位法处理字符串 哈希函数的构造

#include <stdio.h>

Index Hash(const char *Key, int TableSize){
    unsigned int h =0;
    while(*Key !='\0'){
        h=(h<<5)+*Key++;  //h进行位运算。 h左移5位相当于乘以2^5=32。
    }
    return h % TableSize;
}