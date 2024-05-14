//单向链表反转 的实现


#include <stdio.h>
#include <stdlib.h>


struct Node{
    int data;
    struct Node* next;
};

typedef struct Node* PNode;

PNode newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


//反转链表

PNode reverselist(PNode head){
    PNode prev =NULL;
    PNode curr =head;
    PNode next= NULL;

    //在同一条链表上操作。 把结点分为 前一结点、现结点、后一结点
    //循环体里的操作，实际上只是在操作 各个结点的指针，使得他们的反向变反。
    //因为头结点之前没东西，所以一开始curr指针指向head的时，prev指针指向NULL

    while(curr != NULL){
        next = curr->next; // 暂存当前节点的下一个节点 ， 因为要改变curr节点的next指针，防止找不到原next结点
        curr->next = prev; //将当前结点的指针指向 前一个结点prev

        prev =curr; //当前结点curr和下一个结点  都往后移1位
        curr=next;
    }
    return prev;


}