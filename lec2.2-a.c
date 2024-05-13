//堆栈的定义与操作 顺序存储 (数组实现堆栈)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1;


typedef int ElementType ;
typedef int Position;
struct SNode {
    ElementType *Data; /* 存储元素的数组 */
    Position Top;      /* 栈顶指针 */
    int MaxSize;       /* 堆栈最大容量 */
};
typedef struct SNode *Stack;   //Stack是 SNode型指针变量

Stack CreateStack( int MaxSize )
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    //以上两步，给 堆栈S和存储堆栈的数组变量Data分别 动态分配内存，


    S->Top = -1;  //栈顶指针的值 默认是-1，有一个元素入栈，top++
    S->MaxSize = MaxSize;
    return S;//返回指针
}

bool IsFull( Stack S )
{
    return (S->Top == S->MaxSize-1);    //堆栈满，则栈顶指针值为MAXSize-1 ，return 1 也就是return true
}

bool Push( Stack S, ElementType X )
{
    if ( IsFull(S) ) {    // ISFULL 元素返回true 也就是 返回1
        printf("堆栈满");
        return false;
    }
    else {                          //堆栈没满
        S->Data[++(S->Top)] = X;    //栈顶指针先自增1，也就是新元素在Data里的index，，再把X赋值给Data里的index位置）
        return true;
    }
}

bool IsEmpty( Stack S )
{
    return (S->Top == -1);   //空栈的top 值 == -1
}

ElementType Pop( Stack S )
{
    if ( IsEmpty(S) ) {      //先判空
        printf("堆栈空");
        return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
    }
    else
        return ( S->Data[(S->Top)--] );
}