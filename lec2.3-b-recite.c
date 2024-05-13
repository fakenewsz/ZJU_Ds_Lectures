//背诵一次lec2.3-b
//不带头结点的 链表实现对垒
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1

typedef int ElementType;
typedef struct Node* PtrToNode;//定义Node结构之前，可以先取别名

struct Node {
        ElementType Data;
        PtrToNode Next;
};

typedef  PtrToNode Position;

struct QNode{
        Position Front,Rear;
        int Maxsize;
};

typedef struct QNode *Queue;
//判空

bool IsEmpty(Queue Q){
        return (Q->Front == NULL);
}



//判满
//链表不会满

//入队之前需要有创建新节点的函数
PtrToNode newNode(ElementType data){
        PtrToNode temp =(PtrToNode) malloc(sizeof(struct Node));
        temp->Data= data; //输入 入队的数据
        temp->Next = NULL ; // 新节点的Next指针初始化
        return temp;
}


//入队
//Q：类似链表的入队操作，但是之前只操作过 带头结点的链表 的入队，不知道不带头结点的链表队列怎么入队？
//A:实际上不能类比普通链表的入队，因为队列入队不能指定位置，只能在队头入队

void enqueue(Queue Q , ElementType X){
        PtrToNode temp= newNode(X);

        //先判空，才能知道 新结点的Next指针的操作
        //如果队列为空，则新结点  既是 队头又是队尾， 则要操作队列QNode的Front 、Rear指针指向newnode
        if(IsEmpty(Q)){
            Q->Front=Q->Rear=temp;
        }else{
            //否则将新节点添加到队列尾部，并更新队尾指针
            Q->Rear->Next=temp;
            Q->Rear = temp;

        }




}




//出队

ElementType DeleteQ(Queue Q){
        //定义2个临时变量，一个存储结点结构，一个保存 结点的data
        ElementType tempData;
        Position Frontcell;//如果不是动态分配内存后要free 出队结点， 不用临时存储结点的指针
        //照例，删除前先判空
        if(IsEmpty(Q)){
            printf("stack is empty");
            return ERROR;
        }else{
            Frontcell = Q->Front;//把要删除的队头元素保存下来
            if(Q->Front == Q->Rear ) {//若只有一个元素
                Q->Front = Q->Rear = NULL;//把前后指针归零
            }
            else{
                Q->Front=Q->Front->Next;//跳过1个结点指
            }
            tempData=Frontcell->Data;
            free(Frontcell);
            return tempData;
        }
}