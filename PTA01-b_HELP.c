#include<stdio.h>
int main(){
    int max=0,now=0,N,arr[10005],left=0,begin=0,right=0;
    scanf("%d",&N);
    scanf("%d",arr);
    /*我们要先判断一个数的情况，如果不判断的话，max初始值为0,在赋值的过程中max不可能小于0，但确实存在负数的情况*/
    max=now=arr[0];
    for(int i=1;i<N;i++){
        scanf("%d",arr+i);
        if(now>=0)
            now+=arr[i];
        else{
            now=arr[i];
            begin=i;            //begin表示当前最大和的开始位置
        }
        if(now>max){    //如果当前最大和比结果大则更新结果以及起始位置
            right=i;
            left=begin;
            max=now;
        }
    }
    if(max<0){               //如果最终结果为负数，则输出首尾元素
        max=0;
        left=0;
        right=N-1;
    }
    printf("%d %d %d",max,arr[left],arr[right]);
    return 0;
}