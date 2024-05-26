//02-线性结构3 Reversing Linked List
//https://pintia.cn/problem-sets/1738108464136978432/exam/problems/type/7?problemSetProblemId=1738108464208281606&page=0

//一开始看不懂题目的输入和输出之间的算法。后发现是少看了题目一个词。
//题目意思是 链表里每满K个结点的结点组， 都要逆转。不满K个的节点组，不逆转


#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100001

typedef struct LNode *List;

struct LNode{
    int Addr;
    int Data;
    int NextAddr;
    List Next;
};

List FormList(int FirstAdd, int N, int *pn)
{
    //    struct LNode LN[MaxSize];
    List head;
    int tmpAddr;  //as the index of the original array
    int i;
    int Addr[MaxSize], Data[MaxSize], NextAddr[MaxSize];
    struct LNode LN[N + 1];
    LN[0].NextAddr = FirstAdd;
    for(i = 0; i < N; i++){
        scanf("%d", &tmpAddr);
        scanf("%d %d", &Data[tmpAddr], &NextAddr[tmpAddr]);
    }
    i = 1;
    while(1){
        if(LN[i - 1].NextAddr == -1){
            LN[i - 1].Next = NULL;
            (*pn) = i - 1;
            break;
        }
        LN[i].Addr = LN[i - 1].NextAddr;
        LN[i].Data = Data[LN[i].Addr];
        LN[i].NextAddr = NextAddr[LN[i].Addr];
        LN[i - 1].Next = LN + i;  //?
        i++;
    }
    head = LN;
    return head;
}

void PrintList(List L)
{
    List p;
    p = L;
    while(p->Next){
        p = p->Next;
        if(p->NextAddr == -1)
            printf("%05d %d %d\n", p->Addr, p->Data, p->NextAddr);
        else
            printf("%05d %d %05d\n",p->Addr, p->Data, p->NextAddr );
    }
}

List Reverse(List head, int K)
{
    int cnt = 1;
    List newP, old, tmp;
    newP = head->Next;
    old = newP->Next;
    while(cnt < K){
        tmp = old->Next;
        old->Next = newP;
        old->NextAddr = newP->Addr;
        newP = old;
        old = tmp;
        cnt++;
    }
    head->Next->Next = old;
    if(old)
        head->Next->NextAddr = old->Addr;
    else
        head->Next->NextAddr = -1;
    return newP;
}

int main(int argc, char const *argv[])
{
    int FirstAdd, N, K;
    int i, j;
    int num = 0;
    int *pn = &num;
    List L;
    scanf("%d %d %d", &FirstAdd, &N, &K);
    L = FormList(FirstAdd, N, pn);
    List p, rp;
    p = L;
    rp = NULL;
    if(K <= num){
        for(i = 0; i < (num/K); i++){
            rp = Reverse(p, K);
            p->Next = rp;  //更新p
            p->NextAddr = rp->Addr;  //NextAddr的变换尤为重要
            for(j = 0; j < K; j++)
                p = p->Next;
        }
    }
    PrintList(L);
    return 0;
}