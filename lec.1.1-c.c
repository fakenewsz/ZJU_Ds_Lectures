//改进lec.1.1-2里 包含重复代码的部分，把测时间的代码写成函数

#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAXN 100000

double duration;
clock_t start, stop; // clock_t 是clock()函数返回的变量类型
double a[MAXN]; /*存储多项式的系数 */
double f1(int n, double a[], double x);
double f2(int n,double a[], double x);
void estimate(double (*func)(int n ,double a[],double x));


// 【Q】：此处数组a[]需要从main()函数拿出，变成全局变量，否则 estmate()函数里 func(MAXN-1,a,1.1)会提示找不到a指代的变量

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
    // Function body here
    int i;
    double p=a[0];
    for(i =1;i<=n;i++){
        p+=(a[i]*pow(x,i));
    }
    return p;
}

double f2(int n,double* a,  double x) { // (double *)a 和 double a[] 都代表指向数组a的指针

    // 秦九韶 的 多项式算法
    int i;
    double p=a[n];
    for(i=n;i>0;i--){
        p=a[i-1]+x*p;
    }

    return p;
}

