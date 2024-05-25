#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (x >= y ? x : y) //定义的宏，用来取最大值

typedef struct AVLNode *Tree;
typedef struct AVLNode{
    int val; //结点的值
    Tree left; //左子树
    Tree right; //右子树
    int height; //该结点的高度
}Node;

Tree insert(Tree AVL, int val);
Tree leftRotation(Tree T1);
Tree leftRightRotation(Tree T1);
Tree rightRotation(Tree T1);
Tree rightLeftRotation(Tree T1);
int getHeight(Tree T1);

int main(){
    int i, N;
    scanf("%d", &N); //输入的N
    if(N){
        Tree AVL = NULL;
        int val;
        for(i=0; i<N; i++){
            scanf("%d", &val);
            AVL = insert(AVL, val); //在线插入结点
        }
        printf("%d\n", AVL->val); //输出根节点的值
    }
    return 0;
}

Tree insert(Tree AVL, int val){
    if(!AVL){ //若树空，则创建一个空树
        AVL = (Tree)malloc(sizeof(Node));
        AVL->val = val;
        AVL->left = AVL->right = NULL;
        AVL->height = 0;
    }
    else if(AVL->val > val){ //树不空且新插入的结点值小，应该往左子树插
        AVL->left = insert(AVL->left, val); //递归直到最底层插入新结点
        if(getHeight(AVL->left) - getHeight(AVL->right) == 2){ //平衡被破坏
            if(AVL->left->val > val) //插入的值小于左子树，即插在左子树的左边
                AVL = leftRotation(AVL); //执行LL旋转
            else //插在了左子树的右边
                AVL = leftRightRotation(AVL); //执行LR旋转
        }
    }
    else if(AVL->val < val){ //树不空且新插入的结点值大，应该往右子树插
        AVL->right = insert(AVL->right, val); //递归直到最底层插入新结点
        if(getHeight(AVL->left) - getHeight(AVL->right) == -2){ //平衡被破坏
            if(AVL->right->val < val) //插入的值大于右子树，即插在右子树的右边
                AVL = rightRotation(AVL); //执行RR旋转
            else //插在了右子树的左边
                AVL = rightLeftRotation(AVL); //执行RL旋转
        }
    }
    //更新树高
    AVL->height = max(getHeight(AVL->left), getHeight(AVL->right)) + 1;

    return AVL;
}

Tree leftRotation(Tree T1){
    Tree T2 = T1->left; //记录破坏者的父结点
    T1->left = T2->right; //将破坏者父结点的右子树接到发现者的左子树上
    T2->right = T1; //将破坏者的父结点移动到发现者的位置上
    //更新树高
    T1->height = max(getHeight(T1->left), getHeight(T1->right)) + 1;
    T2->height = max(getHeight(T2->left), T1->height) + 1;

    return T2;
}

Tree leftRightRotation(Tree T1){
    T1->left = rightRotation(T1->left);

    return leftRotation(T1);
}

Tree rightRotation(Tree T1){
    Tree T2 = T1->right;
    T1->right = T2->left;
    T2->left = T1;
    T1->height = max(getHeight(T1->left), getHeight(T1->right)) + 1;
    T2->height = max(getHeight(T2->right), T1->height) + 1;

    return T2;
}

Tree rightLeftRotation(Tree T1){
    T1->right = leftRotation(T1->right);

    return rightRotation(T1);
}

int getHeight(Tree AVL){
    if(AVL)
        return AVL->height;
    else
        return 0;
}

