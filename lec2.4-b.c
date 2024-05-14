// 多项式乘法
//链表实现

#include <stdlib.h>
#include <stdio.h>


struct  PolyNode{
    int coef;
    int exp;
    struct PolyNode *link;
};


typedef struct PolyNode *Polynominal;

Polynominal Read();

Polynominal Mult(Polynominal P1, Polynominal P2);

Polynominal Add(Polynominal P1, Polynominal P2);
void printpoly(Polynominal P);


void Attach(int c, int e, Polynominal *pRear){
    //把新结点的数据 c、e 加到原结果多项式尾结点后，输出新的结果多项式
        Polynominal P;
        P=(Polynominal)malloc(sizeof(struct PolyNode));
        P->coef = c;
        P->exp = e;
        P->link = NULL;
        (*pRear)->link= P;
        *pRear= P ;

}


Polynominal Read(){
    int N,c,e;
    Polynominal Rear,P,temp;
    scanf("%d",&N);//N表示输入 多项式的项数

    //初始化结点P
    P=(Polynominal)malloc(sizeof(struct PolyNode));
    P->link = NULL;

    Rear = P; //创建一个空节点，把多项式尾结点指针Rear指向空结点

    while(N--){
        scanf("%d %d",&c,&e);//NOLINT
        Attach(c,e,&Rear);
    }
    //记得删除临时生成的头结点P， 所以需要另一个临时指针变量temp
    temp = P;
    P = P->link; //链表里删除 用跳指
    free(temp);

    return P;
}

Polynominal Mult(Polynominal P1, Polynominal P2){
    Polynominal P ,Rear, t1,t2,t;   //t2用于最后一步删除添加的头结点时，临时存储结点
    int c, e;

    //先确定要相乘的2个多项式 没有一个为空，否则结果直接是0
    if(!P1 || !P2){
        return NULL;
    }
    //操作跳项要改变指针，为了不改变P1 ，P2 ，需要2个临时变量存储P1 ，P2的初始值
    t1=P1;
    t2 = P2;
    //初始化结果多项式
    P=(Polynominal) malloc(sizeof(struct PolyNode));
    P->link =NULL;
    Rear = P; //Rear指针指向P

    //先用P1 的 第1项，分别乘以P2的每一项 ,得到结果多项式P
    while(t2){
        Attach(t1->coef *t2->coef,t1->exp+t2->exp,&Rear);
        t2=t2->link;
    }
    t1=t1->link;//第一项用过后，接下来的处理跳过t1的第一项

    while(t1){
        t2=P2;//刷新t2的值到初始值
        Rear =P;//刷新Rear指针
        while(t2){
            //先计算要插入结果多项式的数字
            c= t1->coef * t2->coef;
            e= t1->exp + t2->exp;

            //怎么把新的项插入已知的 有序的多项式中？ 怎么决定插入位置？
            //判断指数的大小。 待插入项的指数大小夹在哪2项中间，就插入在哪2项之间

            while(Rear->link != NULL && Rear->link->exp > e){//得加一个判断Rear指向的P不为空
                //注意这里是判断e和Rear指的下一项的指数的大小关系
                //rear游离在结果多项式体 外
                Rear=Rear->link ; //逐个扫描Rear指向的链表多项式P
            }
            //退出循环后，Rear指向的那项的后一项，指数不大于e，可能==e可能<e
            //所以这里还要分2种情况判断
            if(Rear->link->exp == e && Rear->link !=NULL){
                //如果指数相等，则系数相加
               // Rear->link->exp +=e;
                if(Rear->link->coef+c !=0){  //系数!=0时，才保留
                    Rear->link->coef +=c;
                }else{  //否则删除结点
                    t = Rear ->link;
                    Rear->link = t->link;
                    free(t);
                }
            }else{
                //如果指数小于e，则插入c、e
                //创建临时结点t
                t=(Polynominal) malloc(sizeof(struct PolyNode));
                //赋值
                t->coef = c;
                t->exp=e;
                //结点t 接到结果多项式链表上
                //常规链表插入结点操作
                t->link= Rear->link;
                Rear->link= t;
                Rear= Rear->link;
            }
            t2=t2->link;
        }
        t1=t1->link;
    }

//计算完毕还需要返回结果多项式
    //返回前删除空的头结点
    //所以需要临时变量t2
    t2= P;
    P=P->link;
    free(t2);
    return P;
}


void printpoly(Polynominal P){
    int flag=0;

    //先判空
    if(!P){
        printf("0 0\n");
        return ;
    }

    while(P){
        if(!flag){ //调整输出格式
            flag =1;
        }else{
            printf(" ");
        }
        printf("%d %d",P->coef,P->exp);
        P=P->link;
    }
}