#include <stdio.h>
#include <time.h>
#include <math.h>



double duration;
clock_t start, stop; // clock_t 是clock()函数返回的变量类型

#define MAXN 100000
double f1(int n, double a[], double x);
double f2(int n,double a[], double x);

int main() {
    int ii;
    double a[MAXN]; /*存储多项式的系数 */

    for (ii = 0; ii < MAXN; ii++)
        a[ii] = (double)ii;

    double duration1, duration2;

    start = clock(); // start 里面存储的是，此时的tick值
    f1(MAXN - 1, a, 1.1);
    stop = clock();  // stop 里同上， 两tick值相减就是 函数运行所用时钟周期
    duration1 = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("ticks1 = %lf\n", (double)(stop - start));
    printf("duration1 = %6.2e\n", duration1);

    start = clock();
    f2(MAXN - 1, a, 1.1);
    stop = clock();
    duration2 = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("ticks2 = %f\n", (double)(stop - start));
    printf("duration2 = %6.2e\n", duration2);

    return 0;
}

double f1(int n, double a[], double x) {
    // Function body here
    int i;
    double p=a[0];
    for(i =1;i<=n;i++){
        p+=(a[i]*pow(x,i));
    }
    return p;
}

double f2(int n,double a[],  double x) {
    // 秦九韶 的 多项式算法
    int i;
    double p=a[n];
    for(i=n;i>0;i--){
        p=a[i-1]+x*p;
    }

    return p;
}
