//PTA DS 01-复杂度2 Maximum Subsequence Sum


//Q：本算法怎么处理，子列和相等，输出最小index的情况？比如sample input 里的 1 2 3 4 和 3 7
// 两个子列和相等的话不更新
//A:因为题目要求输出最小的index，所以遇到相同大小的子列和，不需要更新index

#include <stdio.h>

int main(void){
    int i ,n , max ,now,left=0,r=0,begin=0;
    now = max =0;
    int arr[100001];
    scanf("%d",&n);//NOLINT


    //把第一轮输入移出for循环，以处理n==1 只有1个数字的情况
    scanf("%d",arr);//NOLINT
    max=now= arr[0];


    for (i=1;i<n;i++){//left每次开始扫描时，都要记录左边第一个，也就是
        scanf("%d",&arr[i]);//NOLINT
        if(now>=0){                     //这里不写now < 0的情况下的操作，写它的矛盾情况
            now +=arr[i];               //如果新的数字大于0，直接加
                                        //Q:为什么此时begin不赋值？A:begin不是从这个数字开始的，是从上次有变化的开始，
                                        //  即：如果是第一轮，begin是0，如果是后面的轮，begin从上次有效数字开始算起
                                        //Q:那样begin不是永远是连续出现的负数中，最后一个负数的下标？因为只有now<0才给begin赋值
                                        //A:不对，也可能是arr[-3,1],这样begin=1时，也要赋值
                                        //A：真正的目的是： 要使得 now开始累计时，begin赋值完就不变
                                        //Q:那begin应该是i+1？？
                                        //A:注意，now>max ，时 begin也有 一个赋值
        }else{
            now= arr[i];
             begin=i;                    //begin 和left都储存当前最大和的开始位置,此处先存下begin，等待继续扩大

        }

        if(now > max){      //如果本次子列和最大，再开始更新 左端和右端
                            //Q:按题目要求，这里得是now >=max  ,然而这样写会报错，写>号反而不会报错
                            //因为题目要求输出最小的index，所以遇到相同大小的子列和，不需要更新index
            max = now;
            r=i;
            left=begin;
        }

    }
    if(max<0){
        max =0;
        left=0;
        r=n-1;
    }


    printf("%d %d %d",max,arr[left],arr[r]);
    return 0;
}