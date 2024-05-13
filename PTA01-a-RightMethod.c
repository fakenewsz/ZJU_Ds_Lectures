//PTA DS编程题01-复杂度1 最大子列和问题
//自己想了个，先输入完数组，再在线处理的算法，后来发现，这是离线处理

//参考了这篇：https://blog.csdn.net/fshool/article/details/107118937  后，自己写个

#include <stdio.h>

const int n =100001 ;
int arr[n];
int main(){
    int t ,now ,max,i;
    now = max =0;

    scanf("%d",&t);//NOLINT

    for ( i=0;i<t;i++){
       scanf("%d",&arr[i]);//NOLINT
       now += arr[i];
       if(now > max){
           max =now;
       }else if(now < 0){  //这里书上用else if ，网友用if 也能跑过测试
           now=0;
       }
    }

    printf("%d",max);
    return 0;
}