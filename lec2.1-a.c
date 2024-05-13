//线性表的定义与操作 ,顺序表


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define elementtype int ;
#define MAXSIZE 10;
typedef int position;
typedef struct lnode *list;
struct lnode{
    elementtype data [MAXSIZE];
    position last;
};


//初始化

list makeempty(){
    list l;
    l = (list )malloc(sizeof(struct lnode));
    l->last = -1;//  空链表就是-1. 如果只有头结点 l->last==0
    return l;
}


//查找

#define ERROR -1
position find(list l, elementtype x){
    position i=0;
    while(i<=l->last &&& l->data[i]!= x){
        i++;
    }
    if(i> l->last){
        return ERROR;  //没找到的情况
    }else{
        return i;//找到后返回存储位置
    }
}

//插入

bool insert(list l,elementtype x ,position p){
    //在l的指定位置p 前，插入新元素x
    position i;
    if(l->last == MAXSIZE-1){
        printf("表满");
        return false;
    }
    if(p<0|| p> l->last+1){
        printf("位置不合法");
        return false;
    }
    for(i=l->last; i>=p;i--){
        l->data[i+1] = l->data[i];
    }
    l->data[p]=x;
    l->last++;
    return true;

}
//删除
bool delete(list l , position p){
    position i;

    if(p<0 || p> l->last){
        printf("位置%d不存在元素",p);
        return false;
    }

    for (i=p+1;i<= l->last;i++){
        l->data[i-1]=l->data[i]; //删除p位置元素,是把p覆盖
    }
    l->last--;
    return true;

}


