//习题2.8 输出全排列
//https://pintia.cn/problem-sets/434/exam/problems/type/7?problemSetProblemId=5811&page=0

//思路
//这里自己只能想到 列出所有可能性再输出。     且只能实现到输入数组部分。

#include <stdio.h>


void PrintList(int n);
int main(void){
    int n;
    scanf("%d",&n);

    PrintList(n);
    return 0;
}

void PrintList(int n){

    int i;
    int a[n];
    for(i=0;i<n;i++){
        a[i]=i+1;
        printf("%d",a[i]);
    }
}