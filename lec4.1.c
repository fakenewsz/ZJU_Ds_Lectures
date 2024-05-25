//二叉搜索树的查找、 插入、删除操作



//尾递归实现二叉搜索树的查找
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * BinTree;
typedef BinTree Position;
struct TreeNode{
    int Data;
    Position  Left, Right;
};

//尾递归实现查找指定元素
Position Find(int X, BinTree BST){
    if(!BST)return  NULL;
    if(X>BST->Data){
        return Find(X,BST->Right);
    }else if(X<BST->Data){
        return Find(X,BST->Left);
    }else{
        return BST;
    }
}
//迭代函数实现

Position IterFind(int X, BinTree BST){
    while(BST){
        if(X>BST->Data)
            BST = BST->Right;
        else if(X<BST->Data)
            BST = BST ->Left;
        else
            return BST;
    }
    return NULL;
}
//查找最大元素和最小元素

Position FindMin(BinTree BST){
    //二叉搜索树最小的结点一定在最左边
    if(!BST) return NULL;
    else if (!BST->Left)
        return BST;
    else
        return FindMin(BST->Left);
}

Position FindMax(BinTree BST) {
    //迭代实现
        while(BST && BST->Right){
            BST=BST->Right;
        }

    return BST;
}

//插入

BinTree Insert(int X ,BinTree BST){
    if(!BST){
        BST = (BinTree) malloc(sizeof(struct TreeNode));
        BST->Data =X;
        BST->Left =BST->Right=NULL;
    }else{
        if(X<BST->Data){
            BST->Left = Insert(X,BST->Left);
        }else if (X >BST->Data)
            BST->Right = Insert(X,BST->Right);
    }
    return BST;
}

//删除


BinTree Delete(int X,BinTree BST){
    Position  tmp;
    if(!BST) printf("element not found");
    else if(X<BST->Data){
        BST->Left = Delete(X,BST->Left) ;//
    }else if(X>BST->Data)
        BST->Right = Delete(X,BST->Right);
    else{
        //被删除结点有2个子树的情况,在右子树中寻找最小元素，填充结点（值刚好夹在左子树和右子树中间）
        if(BST->Left && BST->Right){
            tmp = FindMin(BST->Right);
            BST->Data =tmp->Data;
            BST->Right = Delete(BST->Data,BST->Right);//取完值，删除被移动的结点(在右子树中找到Data删除)
        }else{//被删除结点 的子结点数为1或0
            tmp=BST;//要删除的结点 的位置用tmp记录
            if(!BST->Left)  //左子树为0 ， 有右子树
                BST = BST->Right;//用右子树替代被删除的结点
            else if (!BST->Right)
                BST =BST->Left;
            free(tmp);
        }
    }
    return BST;
}


//迭代实现 删除操作。效率更高
BinTree iterDelete(BinTree BST, int X) {
    Position Parent = NULL;
    Position Current = BST;

    // 查找要删除的节点及其父节点
    while (Current != NULL && Current->Data != X) {
        Parent = Current;
        if (X < Current->Data) {
            Current = Current->Left;
        } else {
            Current = Current->Right;
        }
    }

    // 如果节点未找到
    if (Current == NULL) {
        printf("要删除的元素未找到\n");
        return BST;
    }

    // 情况1：要删除的节点有两个子节点
    if (Current->Left != NULL && Current->Right != NULL) {
        Position MinNodeParent = Current;
        Position MinNode = Current->Right;

        // 查找右子树中的最小节点
        while (MinNode->Left != NULL) {
            MinNodeParent = MinNode;
            MinNode = MinNode->Left;
        }

        // 替换数据
        Current->Data = MinNode->Data;

        // 现在删除 MinNode
        //MinNode可能是 原右子树的左子树 的 左儿子/右儿子，分别判断
        //此时的MinNodeParent是  最小结点的父结点
        if (MinNodeParent->Left == MinNode) {
            //（在二叉搜索树中，最小节点不会有左子节点，但可能有右子节点）。
            // 迭代删除 中要注意这个情况。 递归函数不用特别处理.因为已经包含
            MinNodeParent->Left = MinNode->Right;//被删除的结点是左儿子，就把它的右儿子接到它原来的位置
        } else {
            MinNodeParent->Right = MinNode->Right;
        }
        free(MinNode);
    }
    // 情况2：要删除的节点有一个或没有子节点
    else {
        Position Tmp;
        if (Current->Left == NULL) { // 只有右孩子或无子节点
            Tmp = Current;
            if (Parent == NULL) { // 被删除的是根节点
                BST = Current->Right;
            } else if (Parent->Left == Current) {
                Parent->Left = Current->Right;
            } else {
                Parent->Right = Current->Right;
            }
            free(Tmp);
        } else if (Current->Right == NULL) { // 只有左孩子
            Tmp = Current;
            if (Parent == NULL) { // 被删除的是根节点
                BST = Current->Left;
            } else if (Parent->Left == Current) {
                Parent->Left = Current->Left;
            } else {
                Parent->Right = Current->Left;
            }
            free(Tmp);
        }
    }
    return BST;
}







