#include <stdio.h>
#include <time.h>

clock_t start,stop;
double duration;
void PrintN(int N){
    if(N){
        PrintN(N-1);
        printf("%d\n",N);
    }
    return ;
}

int main(){
    int n =0;
    scanf("%d",&n);
    start=clock();
    PrintN(n);
    stop=clock();
    duration = ((double)(stop - start))/CLK_TCK;
    printf("%.5lfs",duration);
    return 0;
}