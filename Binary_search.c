#include <stdio.h>


int binary(int n ,int *a,int k);
int main(){
    int n=0,k=0;
    int a[5];
    //输入n 、 k  数组a[]
    binary(n,a,k);
    return 0;
}

int binary(int n ,int a[],int k){
    //k是要查找的数字
    int left= 0,right = n-1;
    int mid;
    while(left <= right){
        mid = (left+right)/2;
        if(a[mid]==k){
            return mid;
        }else if(a[mid]<k){//如果 a[mid]小于要找的数字，说明
            left=mid+1;
        }else{
            right=mid+1;
        }
    }
    return -1;
}