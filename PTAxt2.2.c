//习题2.2 数组循环左移
//https://pintia.cn/problem-sets/434/exam/problems/type/7?problemSetProblemId=5653&page=0
//思路：
//发现题目没有要求存储左移后的数组。只要求输出数字组合
//那么直接在原数组上，找左移后的 起始位置，开始输出
//用%符号是关键
#include <stdio.h>


int main(void){

    int i,n,m,t;
    scanf("%d %d",&n,&m);//NOLINT
    int a[n];

  for(i=0;i<n;i++){
      scanf("%d",&a[i]);
  }

  int cnt=0;
  for(i=m;cnt<n;cnt++){ //注意这里cnt 不能= n，否则sample1 会多输出一个4
      if(cnt!=0 ){ //第一位数字前不输出空格
          printf(" ");
      }
      if(i>=n){ //这里要>= ，才能使得输出index连续
          i=i%n;
      }
      printf("%d",a[i++]);
  }
    return 0;
}