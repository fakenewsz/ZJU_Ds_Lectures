//判别二叉树是否同构的实现（不考虑左右顺序）
//思路： 程序分为 主程序+建树程序+判别程序
//需要考虑 二叉树的表示方法、 建树程序、 判别程序 + 输出（简单）

#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null (-1)  //注意define 的替换机制可能 导致歧义。 加括号保证意思不变

//结构数组表示 二叉树结点
struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;
}T1[MaxTree],T2[MaxTree];   //数组T1、T2 每个数组元素都是TreeNode结构体，包含3个成员



Tree BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1,Tree R2);
int main(void){
    Tree  R1, R2; //用数组储存树，所以是int类型，别名Tree
    R1 =BuildTree(T1);  //Q：这里build为什么需要参数？ 没参数不可以吗？
    R2 =BuildTree(T2);  //A：因为BulidTree()函数内部要用数据结构进行操作，所以要传入结构指针
    if(Isomorphic(R1,R2)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    return 0;


}

Tree BuildTree(struct TreeNode *T){
    Tree Root=Null;  //空数返回Root = -1;
    int N,i;
    char cl ,cr;
        //注意：此处要scanf进一个\n 符，否则之后 建树会发生错误
    scanf("%d\n",&N);//NOLINT   之后N行输入N个结点
    int check[N]; //check[]数组里一共N个位置，和总结点数量一样。
    //先判定不是空树


    if(N){
        for(i=0;i<N;i++) check[i]=0;//手动初始化数组元素为0
        for(i=0;i<N;i++){
            scanf("%c %c %c\n",&(T[i].Element),&cl,&cr );//先用char 类型变量cl、cr暂存 left和right的输入
            //如果确定是合法输入，不是‘-’ ，再转化成int 类型输入 结点里
            if(cl!='-'){
                T[i].Left=cl-'0';//做儿子的结点代号赋给 T[i].Left
                check[T[i].Left]=1; //check数组对应位置的判别flag改为1 ，辨别出子结点
                //Q:怎么觉得此处应该是check[i]=1;??
                //A:check[结点代号]=1 意思是这个结点被指向过，所以不可能是根结点
                //这里使用的是 被当前结点 的左指针指向的结点T[i].Left （左儿子）的 代码，如果用check[i]就变成检查本结点
            }else{
                T[i].Left=Null;
            }
            if(cr!='-'){
                T[i].Right=cr-'0';
                check[T[i].Right]=1;
            }else{
                T[i].Right=Null;
            }
        }
        for(i=0;i<N;i++){
            if(!check[i]){ // 数组check下标i位置(和输入的数组T一一对应)的元素==0 ，说明没被访问过。
                break ;    //则T[i]存储的结点是根结点
            }
        }
        Root=i;//因为一定有根结点，所以不管怎么样都执行root = i

    }
    return Root;
}

int Isomorphic(Tree R1, Tree R2){//传入的是树T1、T2的根结点代码 R1 R2
    //一共3+3种情况.
    //整体对比3种。  子树对比3种

    if( (R1 == Null ) && (R2 == Null) )
        return 1;
    if(    (( R1 == Null) && (R2 != Null) )   ||  ((R1!=Null)&&(R2==Null)) )
        //此处写if((R1==Null)||(R2==Null))也是可以的，因为上一句if里有return，
        // 已经排除了走到这步可能出现2个树全为空的状态
        return 0;//其中一整个树为空，另一个不为空，那肯定不是同构

    if(T1[R1].Element != T2[R2].Element)
        return 0;//根结点不同，肯定不是同构

    if((T1[R1].Left==Null)&&(T2[R2].Left==Null)) //树T1、树T2 根结点的左子树都是空
        return Isomorphic(T1[R1].Right ,T2[R2].Right);


    if(    (T1[R1].Left!= Null) && (T2[R2].Left!= Null)  &&
        (T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element)   )
    {
        return (Isomorphic(T1[R1].Left,T2[R2].Left) &&
                Isomorphic(T1[R2].Right,T2[R2].Right) );
    }
    else
    {
        return (Isomorphic(T1[R1].Left,T2[R2].Right) &&
                Isomorphic(T1[R1].Right,T2[R2].Left));
    }
}

