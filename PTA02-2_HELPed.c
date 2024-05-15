//02-线性结构2 一元多项式的乘法与加法运算
//https://pintia.cn/problem-sets/1738108464136978432/exam/problems/type/7?problemSetProblemId=1738108464208281605&page=0


#include <stdlib.h>
#include <stdio.h>


struct PolyNode {
    int coef;
    int exp;
    struct PolyNode * link;
};
typedef struct PolyNode* Polyomial;

Polyomial read();
Polyomial Add(Polyomial P1,Polyomial P2);
Polyomial Mult(Polyomial P1, Polyomial P2);
void printpoly(Polyomial P);
void Attach(int c ,int e, Polyomial *pRear);

int main(void){
    Polyomial P1,P2 ,sum,product;
    P1 = read();
    P2 = read();

    product = Mult(P1,P2);
    sum = Add(P1,P2);
    printpoly(product);
    printpoly(sum);

    return 0;
}


void Attach(int c ,int e ,Polyomial *pRear){
    Polyomial P;
    P=(Polyomial)malloc(sizeof(struct PolyNode));
    //赋值 +初始化指针
    P->coef = c;
    P->exp = e;
    P->link=NULL;
    (*pRear)->link=P;//传进来的是指向Rear的指针，里面存储Rear的地址，要操作的是Rear的值，所以解引用
    *pRear = P; //P设为 结果多项式链表的最后一个结点，传出函数

}

Polyomial read(){
    int N,c,e;
    Polyomial Rear,P,temp;
    scanf("%d",&N);
    P=(Polyomial)malloc(sizeof(struct PolyNode));
    P->link=NULL;
    Rear=P;

    while(N--){
        scanf("%d %d",&c,&e);
        Attach(c,e,&Rear);
    }
    temp = P;
    P=P->link;
    free(temp);
    return P;

}
int Compare(int a,int b){
    if(a>b) return 1;
    else if (a<b) return -1;
    else return 0;
}

Polyomial Add(Polyomial P1, Polyomial P2) {
    Polyomial front, rear, temp;

    rear = (Polyomial) malloc(sizeof(struct PolyNode));
    front = rear;//front 不需要动态分配 内存吗
                 /*
    因为 front 并不是用来存储节点数据的，而是作为结果多项式链表的头指针使用的。
    在此示例中，rear 被初始化为一个临时的空节点，并将其作为 front 的初始值，以便在链表的开头插入节点。
 因此，front 并不需要分配额外的内存，它只是一个指针，用于指向链表的头结点
*/

    //对比指数大小，3个情况分别写函数操作。 用Switch函数，每个块尾部都要break;每操作一项，都要跳项
    int sum;
    while (P1 && P2) {
        switch (Compare(P1->exp, P2->exp)) {
            case 1://P1这项 的指数大
                Attach(P1->coef, P1->exp, &rear);
                P1 = P1->link;
                break;
            case -1:
                Attach(P2->coef, P2->exp, &rear);
                P2 = P2->link;
                break;
            case 0:
                //指数相等，则系数要相加
                //相加为0 就不操作，直接跳项
                sum = P1->coef + P2->coef;
                if (sum) {
                    Attach(sum, P1->exp, &rear);
                }
                P1 = P1->link;
                P2 = P2->link;
                break;
        }
    }

    //可能存在剩下一个多项式还有残余的情况

    while (P1) {
        Attach(P1->coef,P1->exp,&rear);
        P1 = P1->link;
    }
    while(P2){
        Attach(P2->coef,P2->exp,&rear);
        P2=P2->link;
    }

//清理临时结点rear ,空节点front， 其中front 的变量名 沿用，指向变化
    rear->link = NULL;
    temp=front;
    front=front->link;
    free(temp);
    return front;

}
Polyomial Mult(Polyomial P1,Polyomial P2){
    Polyomial P, Rear,t,t1,t2;
    int c,e;
    if(!P1 || !P2) return NULL;
    //存储P1、P2的初始值，用于循环
    t1=P1;
    t2=P2;

    //初始化固定3步走
    P=(Polyomial) malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    //乘法分2步，先用P1的一项乘以P2的每一项

    while(t2){
        //乘就是 系数相乘，指数相加
        Attach(t1->coef*t2->coef, t1->exp+t2->exp,&Rear);
        t2=t2->link;//t2循环跳完每一项
    }
    t1=t1->link; //t1 跳1项

    while(t1){
        t2=P2; //刷新指针变量的值
        Rear=P;
        while(t2){
            //先计算要插入的项的 系数和指数
            c = t1->coef * t2->coef;
            e = t1->exp + t2->exp;
            //接下来把新项 插入已知的、有序的 多项式中。
            //重点是寻找插入位置
            // 方法是判断指数的大小

            while(Rear->link != NULL && Rear->link->exp >e){
                Rear = Rear->link;//逐个扫描
            }
            // 此时剩下 exp = 和< 的情况。继续区分
            if(Rear->link != NULL && Rear->link->exp == e ){
                //指数相等，还可能有2种情况： 系数为0 、不为0
                if(Rear->link->coef + c != 0){
                    Rear->link ->coef +=c;
                }else{
                    t =Rear->link;
                    Rear->link =t ->link; //这里不是Rear = Rear ->link
                    //Q:其实Rear = Rear ->link也行？
                    // A：不可以，因为这里操作的是跳过Rear指的的下一个，是跳过rear->link，而不是Rear
                    free(t);
                }
            }else{//指数小于e，则插入c、e
                t=(Polyomial)malloc(sizeof(struct PolyNode));
                //t->link=NULL;
                t->coef=c;
                t->exp=e;
                //临时节点t 插入结果多项式
                //常规链表插入结点方法。 2指 1 跳
                t->link = Rear->link;
                Rear->link = t;
                Rear =Rear->link;
            }
            t2=t2->link;
        }
        t1=t1->link;
    }

    //计算完毕
    //还差返回 结果多项式 + 删除临时结点

    t2=P;
    P=P->link;
    free(t2);
    return P;

}

void printpoly(Polyomial P){
    int flag =0;
    if(!P){
        printf("0 0\n");
        return ;
    }
    while(P){
        //第一项前无空格，第二项开始， 输出数字前跟1空格
        if(!flag){
            flag=1;
        }else{
            printf(" ");
        }
        printf("%d %d",P->coef,P->exp);
        P=P->link;
    }
    printf("\n");
}