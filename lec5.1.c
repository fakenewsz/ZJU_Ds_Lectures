//堆的定义、建立、判空、判满、插入、删除最大值



#include <stdio.h>
#include <stdlib.h>
#define MaxData 1000;

typedef struct Heapstruct * MaxHeap;
struct  Heapstruct{
    int *Elements;
    int Size;  //当前元素个数
    int Capacity;//最大容量


};

int IsFull(MaxHeap H){
    return (H->Capacity == H->Size);
}

MaxHeap Create(int MaxSize){
    MaxHeap H = malloc(sizeof(struct Heapstruct));//先给整体结构体分配空间
    H->Elements = malloc((MaxSize+1)*sizeof(int ));//再给数组分配空间
    H->Size = 0;
    H->Capacity =MaxSize;
    H->Elements[0]= MaxData; //数组[0]位置不放置堆的元素，放哨兵。哨兵>任意堆元素
    return H;
}


void Insert(MaxHeap H, int item){
    int i;
    //插入前判满
    if(IsFull(H)){
        printf("the MaxHeap is full");
        return ;
    }
    i = ++H->Size;//i指向插入后，堆中的最后一个元素的位置
    // Elements[i/2]是父结点的位置  根据完全二叉树第i个结点的左儿子是第2i个推出
    for(;H->Elements[i/2] < item;i/=2){
        //向下过滤结点
        H->Elements[i] = H->Elements[i/2]; //每个结点的值都被赋给子结点。结点本身的位置留待循环退出后给item
    }
    H->Elements[i] = item;

}
int IsEmpty(MaxHeap H) {
    return H->Size == 0;
}
int DeleteMax(MaxHeap H){
    //从最大堆中取出 最大的元素，并删除元素所在结点
    //取出的最大元素的位置，肯定在最上面， 此时堆的容量=MaxSize-1.但是数组[Size]位置，也就是原堆的最后一个元素，需要变换位置，否则溢出
    //所以想到把原堆的最后一个元素，放到 被删除的最大的元素的位置。
    //再进行调整，保证有序性。
    int Parent,Child;
    int MaxItem,tmp;

    //删除前判空
    if(IsEmpty(H)){
        printf("the MaxHeap is empty");
        return -1;
    }
    MaxItem = H->Elements[1]; //最大值就在根结点。取出
    //用最大堆中的最后一个元素从根结点开始向上过滤下层结点
    tmp = H->Elements[H->Size --];//取出最后一个元素。记得此时堆当前元素量要-1

    for (Parent =1 ; Parent*2 <= H->Size; Parent = Child){//Parent指示 tmp 要放入的位置。一开始假定在最上面的根root位置
        //然后开始把parent 和左右儿子中较大者比较
        //Parent *2> H->Size说明没有左儿子
        Child =Parent *2; //child是parent结点左儿子的值。 左儿子的存在决定右儿子的存在

        if( (Child!=H->Size) && // child == H->Size 时，parent的左儿子child是堆中最后一个元素
            ( H->Elements[Child] < H->Elements[Child + 1] )){//左右子结点比较
            Child++; //Child指向 左右子结点 中较大者
        }

        if(tmp >= H->Elements[Child])//原堆最后一个元素tmp比 parent结点最大的子元素大，那么跳过这个if else循环.
                                     // 这个parent的位置就是tmp要找的位置
            break ;
        else{//否则， tmp作为parent结点，小于子结点中的较大者，不符合最大堆结构，
            H->Elements[Parent] = H->Elements[Child];//此时把 子元素中的最大值，赋给parent结点（交换位置）
        }
        //继续循环
        //循环退出条件有2个：途中找到parent位置，break了。
        // 或者  一直往下，找到第parent个结点已经是叶结点，（说明往上没有比tmp小的结点）把tmp插入这里
        //Q:parent左右儿子里小的那个，及其子结点 如果有适合tmp 的位置，会不会漏掉一些情况？
        //A:不会。输入序列{44 25 36 18 10 33 35 37}，插入37后，在左子树（root结点小的那个子树）下方插入，不影响最大堆的结构
    }
    //到这里，parent就是 tmp 大于parent的两个子结点的位置
    H->Elements[Parent] = tmp;
    return MaxItem;
}
