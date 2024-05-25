//哈夫曼树的构建

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * HuffmanTree;
struct TreeNode{
    int Weight;
    HuffmanTree Left,Right;
};



HuffmanTree Huffman( MinHeap H)
{
    int i;
    HuffmanTree T;
    BuildMinHeap(H);
    for(i=1;i<H->Size; i++){
        //要创建多个新结点T，所以分配内存语句要放在循环内部
        T =malloc(sizeof(struct TreeNode));
        T->Left = DeleteMin(H);//从最小堆中删除一个结点，作为新T的左结点
        T->Right = DeleteMin(H);//同上

        T->Weight = T->Left->Weight +  T->Right->Weight;
        Insert(H,T);//将新T插入最小堆

    }
    T=DeleteMin(H);
    return T;
}
