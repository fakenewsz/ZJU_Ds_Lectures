//背 lec2.3-a ,循环数组创建队列、出队、入队的代码


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERROR -1;

typedef int ElementType ;
typedef int Position;  //数组里的前后位置指针 Front、Rear都 用int类型存储

//从小开始，先创建结点结构
struct QNode{
    ElementType *Data;
    Position Front ,Rear;
    int Maxsize ;
};

//创建队列

typedef  struct QNode *Queue; //队列是QNode类型结构指针

Queue CreateStack(int Maxsize){
    //分配空间
    Queue Q = (Queue)malloc(sizeof(struct QNode)); //队列指针的内存空间大小是struct QNode的大小，不是Queue Q的大小
    Q->Data = (ElementType*)malloc(Maxsize *sizeof(ElementType));
    //初始化指针位置
    Q->Front=Q->Rear=0;
    Q->Maxsize =Maxsize;
    return Q;
}

//判满
bool IsFull(Queue  Q){
    //计算(Rear+1) %数组长度 == Front的结果，可知 循环数组队列是否为满
    return ((Q->Rear+1)% Q->Maxsize == Q->Front);
}

//入队
//2个参数：要入的结构 ， 要加入的data

bool AddQ(Queue Q, ElementType X){
    //照例，入队前先判满
    if(IsFull(Q)){
        printf("stack is full");
        return false;
    }else{
        //先变动要插入的位置Rear+1
        Q->Rear = (Q->Rear+1)%Q->Maxsize;//本来只需要Q->Rear++ ，
                                         // 但为了防止假溢出，必须把 Rear+1的结果Mod 数组长度，实现循环
        //Data数组的Rear 位，输入数据
        Q->Data[Q->Rear]=X; //注意Rear+1位 的结点的Data数组下标是Q->Rear
        return true;
    }
}
//判空
bool IsEmpty(Queue Q){
    //直接判断队列是否是初始状态，就可以知道 是否为空
    return (Q->Front == Q->Rear);
}

//判空之后是删除


ElementType DeleteQ(Queue Q){//出队只需要 改动Front指针

    //数组实现的队列，删除结点不需要 临时变量存储信息
    //删除前先判空
    if(IsEmpty(Q)){
        printf("stack is empty");
        return ERROR;
    }else{
        Q->Front =(Q->Front+1)%Q->Maxsize;//注意这里Front是+1 。 因为空间上，出队入队，都会使得队体向前移动
        return Q->Data[Q->Front];//Q:这里返回的怎么是新位置Front+1的Data？ 而不是删除掉的位置Front的Data？
    }                           //A:因为数组下标从0开始，Front+1 号结点的Data，下标是Front



}