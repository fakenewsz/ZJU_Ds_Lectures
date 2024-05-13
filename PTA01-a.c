//PTA数据结构编程题01-复杂度1 最大子列和问题


//Q：数组大小动态变化怎么办？ A：直接开成最大值1e5 +1
//Q：先输入完数组再处理，就不叫在线处理了。但是能通过
//Q:不用考虑int范围不够大的问题

// 低级处理方法。

#include <stdio.h>
#include <stdlib.h>
int maxSubseq4(int List[],int n);
int main(){


    int n=0,sum=0,i=0;
    scanf("%d",&n);
    if(n<1 || n>1e5){
        return 1;
    }
    int *arr= (int*)malloc(n*sizeof(int));//Q:一开始忘记用n*sizeof(int )，导致报错 段错误

    for (i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    //输入完成

    sum = maxSubseq4(arr,n);

    //计算完成
    if(sum){
        printf("%d",sum);
    }else{
        printf("0");
    }

    return 0;
}

int maxSubseq4(int List[],int n){
    int thisSum =0, maxSum=0;
    int i;
    for(i=0;i<n;i++){
        thisSum+=List[i];
        if(thisSum>maxSum){
            maxSum=thisSum;
        }else if(thisSum<0){
            thisSum=0;
        }
    }

    return maxSum;
}