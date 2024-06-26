/* 图的邻接表表示法 */
#include <stdio.h>
#include <stdlib.h>



#define MaxVertexNum 100    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* 边表的头指针 */   ///这里就形成AdjList[0]->Firstedge(AdjVNode类型)->nextedge (AdjVNode类型)->  这样的结构
    DataType Data;            /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

///从大到小：LGraph包含 AdjList[] G 包含链表结点PtrToAdjVNode FirstEdge
///所以引用的时候是 Graph->G[VertexIndex]. FirstEdge

LGraph CreateGraph( int VertexNum )///注意 初始化图 ，必须给出 顶点个数， 不可能初始化一个没有顶点、没有边的图
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL; /// 指针当然初始化为NULL

    return Graph;
}

void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;

    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;  ///注意这里NewNode 的 邻接点下标赋值为V2
    NewNode->Weight = E->Weight;///E是有向边，所以权重赋值给 NewNode是可行的

    /* 将V2插入V1的表头 */
    ///????????
    /// 常规的链表操作。意思是在原有的链表里加入一个新结点newnode。 原有链表只标记了头结点Graph->G[E->V1].FirstEdge
    ///要插入，也是从链表头开始插入。
    ///插入时，先动新结点的指针， 也就是NewNode->next的指针，指向插入前的链表表头Graph->G[E->V1].FirstEdge
    ///再动原结点的指针，插入后，头结点应该是newnode了，也就是把newnode的值，赋给Graph->G[E->V1].FirstEdge 、
    NewNode->Next = Graph->G[E->V1].FirstEdge;//????
    Graph->G[E->V1].FirstEdge = NewNode;
    ///Graph->G[E->V1].FirstEdge;不是Graph->G[E->V1]->FirstEdge;
    ///因为 'a->b'==' (*a).b ' 左侧a应该是结构体指针,通过解引用结构体指针，得到结构体(*a)
    ///再 引用结构体(*a)里的结构体成员b。表达式就是(*a).b 或者a->b
    /// 再对邻接表进行操作时，Graph->G[E->v1]， 中的数组G[E->V1]是个结构体，所以用.号

    /* 若是无向图，还要插入边 <V2, V1> */
    /* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { //如果有输入边
        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    }

    /* 如果顶点有数据的话，读入数据 */
    for (V=0; V<Graph->Nv; V++)
        scanf(" %c", &(Graph->G[V].Data));

    return Graph;
}