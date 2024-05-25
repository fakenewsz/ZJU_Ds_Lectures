//MOOC 4.3判定是否同一棵二叉树
//也是PAT MOOC 题目集04-4 https://pintia.cn/problem-sets/1738108464136978432/exam/problems/type/7?problemSetProblemId=1738108464208281611&page=0



#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode *Tree;
struct TreeNode{
    int val;
    Tree Left, Right;
    int flag;
};


Tree MakeTree(int N);
Tree Insert(Tree T,int V);
Tree NewNode(int V);
void ResetT(Tree T);
void FreeTree(Tree T);
int Judge(Tree T,int N);
int check(Tree T,int V);

//主函数
int main(void){
    int N , L ,i;
    Tree T;

    scanf("%d",&N);

    while(N){  //函数怎么退出？ 题目有给：读取到N为0时，
        scanf("%d",&L);
        T = MakeTree(N);
        for(i=0;i<L;i++){  //共L行 序列，需要进行判定，每个序列有N个结点。
            if(Judge(T,N)!=0 ) {
                printf("Yes\n");
            }else{
                printf("No\n");
            }
            ResetT(T);//每判断完一个结点，重置临时树T 为初始空树状态
        }
        FreeTree(T);//每判断完一组输入序列，重置临时树T 为初始空树状态，重置T的头结点指针
        scanf("%d",&N);//读取下个输入序列，和已有的树对比
    }

    return 0;
}
Tree NewNode(int V){
    //初始化三部曲。 赋值、指针赋NULL
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->val = V;
    T->Left = T->Right = NULL;
    T->flag = 0;
    return T;
}


Tree MakeTree(int N){
    Tree T;
    int i,V;
    scanf("%d",&V);
    T= NewNode(V);
    for(i=1;i<N;i++){
        scanf("%d",&V);
        T = Insert(T,V);    //把新的值插入到临时树结构体中，形成完整的树
    }
    return T;
}

Tree Insert(Tree T, int V){
    if(T== NULL){//如果要插入 树T 的头结点 等于空，那么说明要插入一个新结点
        T = NewNode(V);
    }else{
        if(V> T->val){
            T->Right = Insert(T->Right,V); //把T结点的右儿子（树结构） 以新值V建树
        }else{                      //要插入的值V == T->val，说明要插入一个相同的值，一般不考虑这个情况。这里默认插入左边
            T->Left = Insert(T->Left,V);
        }
    }
    return T;
}

//判定函数




int check(Tree T, int V)//返回0代表匹配，返回1代表不匹配
{
    if (T->flag != 0){ //flag初始化=0，flag不为0说明该结点前期出现过，到此，树还满足相同的条件
        if(V > T->val) return check (T->Right,V); //根据V的位置，检查左右子树
        else if(V < T->val) return check(T->Left,V);
        else                     return 0; // V ==当前结点的值，说明树和序列相匹配
    }else{
        //当flag == 0,说明该结点在先前未被触及
        if(V == T->val){
            T->flag =1;
            return 1;
        }else{
            return 0;
        }
    }
}

int Judge(Tree T, int N) //返回1 ，代表树和序列匹配，返回0代表不匹配
{
    int i ,V,flag;
    flag =0;
    scanf("%d",&V);

    //先判断root 和 输入序列第1个数字是否匹配，
    if(V!= T->val) flag=1;
    //此处不能直接退出，否则会在没有完整读取本序列的情况下，进入下个序列的判断.
    //这样，本序列没被读取的字符，会被当成下个序列的字符，造成后续结果错误

    //标记一下发现 有输入和结点不匹配


    else T->flag =1;
    for(i=1;i<N;i++){
        //此处要坚持读完本序列的字符
        scanf("%d",&V); //循环读取N-1个结点的val
        if((flag == 0 )&& (check(T,V)==0) ) flag=1;//如果此处已经有结点不匹配，不用check()判断了
    }

    if(flag==1){//flag==1说明有 结点不匹配，直接返回不匹配
        return 0;
    }else{
        return 1;
    }

}
void ResetT(Tree T){
    if(T->Right!=NULL) ResetT(T->Right);
    if(T->Left!=NULL) ResetT(T->Left);
    T->flag=0;//把T的flag标记 也改成初始化状态
}

void FreeTree(Tree T){
        if(T->Left) FreeTree(T->Left);
        if(T->Right) FreeTree(T->Right);
        free(T);
}