//用链表实现多项式加法
#include <stdio.h>
#include <stdlib.h>

struct PolyNode {
    int coef;
    int exp;
    struct PolyNode *link;
};

typedef struct PolyNode * Polynominal;
Polynominal P1,P2;

void Attach(int c, int e , Polynominal *pRear){
    //由于在本函数中需要改变当前结果表达式尾项的指针的值，
    // 所以函数传递进来的是结点指针的地址，*pRear指向尾项
    Polynominal P;
    //初始化临时节点P
    P = (Polynominal)malloc(sizeof(struct PolyNode));
    //赋值
    P->coef = c;
    P->exp = e;
    P->link = NULL;
    //将P指向的临时节点 插入到 当前结果表达式尾项的后面
    (*pRear)->link = P;
    *pRear=P;//此时结果表达式最后一项是P结点，那么*pRear就指向P


}

int compare(int a, int b){
    if(a> b){
        return 1;
    }else if(a == b){
        return 0;
    }else{
        return -1;
    }
}

//加法主函数

Polynominal PolyAdd(Polynominal P1,Polynominal P2){
    Polynominal front ,rear ,temp;
    int sum ;
    //为了方便表头插入，先产生一个临时空结点rear，作为结果多项式表头
    rear = (Polynominal)malloc(sizeof(struct PolyNode));
    front = rear; //front指针记录结果多项式 链表头结点

    //Q:front 和rear有什么用？
    //A:front 标记结果链表的头结点，等下return出函数。
    // rear 一直表示结果多项式尾指针，动态变化
    // 开头的时候front= rear，后，front不变，尾指针rear随着新结点的插入编号

    while(P1 && P2){    //两个多项式都有非0 项待处理时
        switch(compare(P1->exp ,P2->exp)){ //P1链表的第i项 ，和P2链表的第i项,逐项比较指数
            case 1:
                Attach(P1->coef,P1->exp,&rear);//P1指数大，先把P1完整传入结果多项式链表
                //注意这里要取地址&rear.因为rear是结构指针，
                //函数参数表要传入结构指针，得传结构指针的地址，也就是指针的指针，二级指针
                P1=P1->link;
                break ;
            case -1:
                Attach(P2->coef,P2->exp,&rear);
                P2=P2->link;
                break ;
            case 0:
                sum = P1->coef + P2->coef;
                if(sum){
                    Attach(sum,P1->exp,&rear);
                }
                P1=P1->link;
                P2=P2->link;
                break ;
        }
}
//以上结果跑完。 有一个多项式已经被清空，此时可能还剩1个多项式 有项未处理
//将未处理完的多项式的所有结点 依次完整复制到结果多项式中

for(;P1!=NULL;P1=P1->link){//只要P1多项式还不为空， 执行循环内容，并跳项
        Attach(P1->coef,P1->exp,&rear);
}
for(;P2!=NULL;P2=P2->link){
        Attach(P2->coef,P2->exp,&rear);
}

//以上，已经把结果多项式创建完成。

rear->link = NULL; //记得清空 最后一个结点的next指针
temp = front ;   //删除临时创建的front结点，使得结果多项式仅包含表达多项式内容的结点
front = front->link;
free(temp);

return front;





}