//线性表的定义与操作, 链式表
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAXSIZE 10;
typedef int ElementType ; // 不是define ElementType int
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

/* 查找 */
#define ERROR NULL

Position Find( List L, ElementType X )
{
    Position p = L; /* p指向L的第1个结点 */

    while ( p && p->Data!=X )//p结点不是空 ,且, p结点的数据data要找的X时,  跳过找下个
        p = p->Next;

    /* 下列语句可以用 return p; 替换 */
    if ( p )
        return p;   //找到了X,那p不会加到NULL,那么就返回位置p
    else
        return ERROR; //没找到X,最后一次p=p->next使得P=NULL. 返回错误提示
}

/* 带头结点的插入 */
/*注意:在插入位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是链表结点指针，在P之前插入新结点 */
bool Insert( List L, ElementType X, Position P )//给L链表的P位置插入X元素
{ /* 这里默认L有头结点 */
    Position tmp, pre;

    /* 查找P的前一个结点 */
    for ( pre=L; pre!= NULL&&pre->Next!=P; pre=pre->Next ) ;//Q:这里循环体里没有 执行内容, 本循环用来干什么?
                                                            //A:用来使得pre->next指向P
    if ( pre==NULL ) { /* P所指的结点不在L中 */
        printf("插入位置参数错误\n");
        return false;
    }
    else { /* 找到了P的前一个结点pre */
        /* 在P前插入新结点 */
        tmp = (Position)malloc(sizeof(struct LNode)); /* 申请、填装结点 */
        tmp->Data = X;
        tmp->Next = P;
        pre->Next = tmp;
        return true;
    }
}

/* 带头结点的删除 */
/*注意:在删除位置参数P上与课程视频有所不同，课程视频中i是序列位序（从1开始），这里P是拟删除结点指针 */
bool Delete( List L, Position P )
{ /* 这里默认L有头结点 */
    Position pre;

    /* 查找P的前一个结点 */
    for ( pre=L; pre&&pre->Next!=P; pre=pre->Next ) ;//跑完循环后pre->next指向P或者NULL
    if ( pre==NULL || P==NULL) { /* P所指的结点不在L中 */  //排除NULL 的情况
        printf("删除位置参数错误\n");
        return false;
    }
    else { /* 找到了P的前一个结点pre */
        /* 将P位置的结点删除 */
        pre->Next = P->Next;
        free(P);
        return true;
    }
}