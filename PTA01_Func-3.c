//01-复杂度3 二分查找
//https://pintia.cn/problem-sets/1738108464136978432/exam/problems/type/6?problemSetProblemId=1738108464208281600&page=0





#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

/* 你的代码将被嵌在这里 */

Position BinarySearch(List L, int X){
    int left , mid, right ;
    left=0; // 这里left取0的意义是 使得第一个mid 刚好= right/2. 不意味着和for循环i从0开始的意义一样。
    right=L->Last ;//这里right 不能是Last-1， 否则 会 找不到最后一个数

//Q:不需要for 循环 记录index吗？
    //Q：while循环里没有自增，怎么跳出循环的？
    //A:left 和right 的值会变，  以此为循环跳出依据
   while(left <= right){
       printf("a");
       //mid = (left + right)/2;错误
       mid = left +(right-left)/2;

       if(L->Data[mid]< X){
           left = mid +1;
       }else if(L->Data[mid]>X){
           right = mid-1;
       }else{
           return mid;
       }
   }
   return NotFound;

}