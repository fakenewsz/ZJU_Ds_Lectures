//图的邻接矩阵表示法 -- 简单版，适合考试


#include <stdio.h>
#define MAXN 10


int G[MAXN][MAXN],Nv,Ne;
void BuildGraph(){
    int i,j,v1,v2,w;
    scanf("%d",&Nv);
    /*create graph*/
    for(i =0;i<Nv;i++){
        for (j=0;j<Nv;j++){
            G[i][j]=0;//或者 = infinity（有权图）
        }
    }
    scanf("%d",&Ne);
    for(i=0;i<Ne;i++){
        scanf("%d %d %d",&v1,&v2,&w);
        /*insert edge*/
        G[v1][v2]=w;
        G[v2][v1]=w;
    }

}


