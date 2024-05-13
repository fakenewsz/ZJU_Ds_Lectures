//数据结构教材第1章课后习题1.5，不会做。

#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAXN 100

double duration;
clock_t start, stop;
double a[MAXN];
double f1(int n, double a[], double x);
double f2(int n,double a[], double x);
void estimate(double (*func)(int n ,double a[],double x));



int main() {
    int i;
    for (i = 0; i < MAXN; i++)
        a[i] = (double)i;
    estimate(f1);
    estimate(f2);
    return 0;
}
void estimate(double (*func)(int n ,double a[],double x) ){

    start= clock();
    func(MAXN-1,a,1.1);
    stop=clock();
    duration=((double )(stop-start))/CLOCKS_PER_SEC;
    printf("ticks2 = %f\n", (double)(stop - start));
    printf("duration2 = %6.2e\n", duration);

}


double f1(int n, double a[], double x) {
    // 直接法
    int i;
    double p=a[0];
    for(i =1;i<=n;i++){
        p+=(a[i]*pow(x,i));
    }
    return p;
}

double f2(int n,double* a,  double x) {

    // 秦九韶 的 多项式算法
    int i;
    double p=a[n];
    for(i=n;i>0;i--){
        p=a[i-1]+x*p;
    }

    return p;
}

