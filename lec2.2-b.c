//链表实现堆栈



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define ERROR -1;


typedef int ElementType ;


typedef struct SNode *PtrToSNode;
struct SNode {
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;   //Stack是 SNode *类型指针变量

Stack CreateStack( )
{ /* 构建一个堆栈的头结点，返回该结点指针 */
    Stack S;

    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;   //空栈的next指针默认指向NULL
    return S;   //函数返回 指针
}

bool IsEmpty ( Stack S )
{ /* 判断堆栈S是否为空，若是返回true；否则返回false */
    return ( S->Next == NULL );
}



//Q:压栈前不需要判满？？？？ A：因为是链表实现+动态分配内存， 一般不考虑内存满的情况
bool Push( Stack S, ElementType X ) //Push(<dest> , <content>)
{ /* 将元素X压入堆栈S */
    PtrToSNode TmpCell;    //要用一个 临时 变量  存储新的SNode结构里的数据， 再把临时变量当做新结点放入原链表

    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;          //赋值
    TmpCell->Next = S->Next;    //先插入新结点
    S->Next = TmpCell;          //再把老的上个结点，指向新结点
    return true;
}

ElementType Pop( Stack S )
{ /* 删除并返回堆栈S的栈顶元素 */
    PtrToSNode FirstCell;
    ElementType TopElem;    //需要一个临时变量来存储Data

    if( IsEmpty(S) ) {
        printf("堆栈空");     //删除前照例先判空
        return ERROR;
    }
    else {
        FirstCell = S->Next;            //S->Next指向firstcell（要弹出的结点的完整结构）
        TopElem = FirstCell->Data;      //读取需要的信息（要弹出的结点的Data）
        S->Next = FirstCell->Next;      //S->Next = S->Next ->Next。S跳过一个元素，来指向。  跳过的元素就是出栈的元素Firstcell
                                        //Q: 栈里有元素的情况下，S->Next指向什么？NULL?
        free(FirstCell);   //malloc的空间记得 free
        return TopElem;  //返回需要的数据，也就是Data
    }
}