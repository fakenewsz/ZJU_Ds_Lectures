//04-树5 Root of AVL Tree
//套用lec4.2 AVL树的调整 的代码


#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

AVLTree SingleRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);
int Max ( int a, int b )
{
    return a > b ? a : b;
}

int GetHeight(AVLTree T){
    if(T == NULL ){
        return 0;
    }else{
        return T->Height;
    }
}

AVLTree SingleLeftRotation ( AVLTree A ) //单左失衡，L旋转，所以要右旋，顺时针旋转.
{ /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */
    //一共两次互换。
    // 定义pivot后，先操作pivot ->Right,替代pivot 的位置，再互换现在的pivot->Right 和原root结点 的位置。完成右旋/左失衡 的调整
    //Q:不知道为什么函数名字 和函数内容相反

    //简单总结只有3步：
    //1。确定旋转类型，从而确定要改变从属的结点。
    //定义pivot ，然后把pivot的从属结点先接到原 root结点，让位
    //让位后就可以把原root 结点接到 pivot 子结点让出的位置上

    AVLTree B = A->Left;// 把pivot B 作为新树的 root结点  ，B在原来A->Left的位置
    A->Left = B->Right;//把 pivot B的右结点接到 原root结点A 的左边。 让出B->Right的位置
    //A->Left= A->Left->Right
    B->Right = A;//A结点接到 B 的右边，填充B->Right
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1; //注意，树的高度=最深路径边数=子树高度+1
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}


AVLTree DoubleLeftRightRotation ( AVLTree A )     //不是做2次左旋。是LR旋转。
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

AVLTree SingleRightRotation(AVLTree A){  //R旋转
    AVLTree B  = A->Right;
    A->Right = B->Left;
    B->Left =A;
    A->Height =Max(GetHeight(A->Left), GetHeight(A->Right))+1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;
    return B;
}

AVLTree DoubleRightLeftRotation(AVLTree A){//RL旋转
                                            // root结点A 有一右子结点B，B有一左子结点C
                                            //思路：先操作子树的旋转， 再旋转原root  。 右结点失衡，就右旋，函数名相反--singleleft。

    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);//再左旋root结点。
}



/*************************************/
/* 对称的右单旋与右-左双旋请自己实现 */
/*************************************/

AVLTree Insert( AVLTree T, ElementType X ) { /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T) {                              /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree) malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */

    else if (X < T->Data) {
        /* 插入T的左子树 */
        T->Left = Insert(T->Left, X);
        /* 如果需要左旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
            if (X < T->Left->Data) {
                T = SingleLeftRotation(T); /* 左单旋 */
            } else {
                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
            }
        } /* else if (插入左子树) 结束 */
    }
    else if (X > T->Data) {
        /* 插入T的右子树 */
        T->Right = Insert(T->Right, X);
        /* 如果需要右旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == -2) {
            if (X > T->Right->Data) {
                T = SingleRightRotation(T); /* 右单旋 */
            }
            else {
                T = DoubleRightLeftRotation(T); /* 右-左双旋 */
            }                                   /* else if (插入右子树) 结束 */
        }
    }

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}


int main(){

    int i ,N;
    scanf("%d",&N);
    if(N){
        AVLTree AVL=NULL;   //不需要maketree,因为 insert()函数里 处理了空树的情况。
        int val;
        for(i=0;i<N;i++){
            scanf("%d",&val);
            AVL = Insert(AVL,val);
        }
        printf("%d\n",AVL->Data); //这里不是输出AVL->Height .别看错题目
    }

    return 0;
}