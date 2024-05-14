//02-线性结构1 两个有序链表序列的合并



#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}



/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ){
    //建立一个新的头结点L，作为储存结果的链表结点

    List L ,head,l1,l2;// l1 l2 有什么用？
    l1= L1->Next;//L1、L2结点本身为空的头节点， 所以取L1、L2有内容的部分为l1、l2
    l2=L2->Next;

    //初始化L结点
    L= (List) malloc(sizeof(List));
    L->Next = NULL;
    head = L;//head标记L (L所有结点都带内容，所以需要个头结点head来 使 L 传出函数体)

    while(l1!= NULL && l2!= NULL ){//合并前先判空
        if(l1->Data <= l2->Data){  //l1和l2 各项比较data大小，大的先传入L
            L->Next = l1;//把l1 的结点 传入L
            l1=l1->Next;// L 和l1都 跳到下一项
            L=L->Next;
        }else{
            L->Next =l2;
            l2= l2->Next;
            L= L->Next;
        }
    }
    //当其中一个链表已经排完了之后，另一个链表剩下的节点直接贴上去
    if (l1 == NULL)
        L->Next = l2;
    if(l2== NULL)
        L->Next = l1;

    //把输入的L1、L2 置为空链表
    L1->Next=NULL; //头结点指针指向空，后面的内容丢失，就等于置为空链表。
    L2->Next=NULL; //虽然没有free掉L1、L2后面的结点
    return head;


}