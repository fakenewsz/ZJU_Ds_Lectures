//用循环数组实现队列

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERROR -1;

typedef int ElementType ;



typedef int Position;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

Queue CreateQueue( int MaxSize )  //传入MAXSIZE
{   //还是要为整个队列 、 队列里的Data 分别动态分配内存  。注意结点只需要1个sizeof 。 Data需要MAXSize个
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));

    Q->Front = Q->Rear = 0;//起始状态 front和rear指针指向相同位置
    Q->MaxSize = MaxSize;     //输入MAXSIZE
    return Q;
}

//判满
bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

//入队
bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

//判空
bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}


//删除
ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) {
        printf("队列空");
        return ERROR;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}