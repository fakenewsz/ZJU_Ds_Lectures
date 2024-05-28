/* 归并排序 - 循环实现 */
/* 这里Merge函数在递归版本中给出 */

#include <stdlib.h>
#include <stdio.h>
typedef  int ElementType;

///Merge函数和 递归版本一样
void Merge( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; /* 左边终点位置 */
    Tmp = L;         /* 有序序列的起始位置 */
    NumElements = RightEnd - L + 1;

    while( L <= LeftEnd && R <= RightEnd ) {
        if ( A[L] <= A[R] )
            TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
        else
            TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
    }

    while( L <= LeftEnd )
        TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
    while( R <= RightEnd )
        TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */

    for( i = 0; i < NumElements; i++, RightEnd -- )
        A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}

/* length = 当前有序子列的长度*/
void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
{ /* 两两归并相邻有序子列 *////    把A[] 导入到 TmpA[]
    int i, j;

    for ( i=0; i <= N-2*length; i += 2*length ) {
        ///这里将两个子序列归并 到 剩下不到 2个子列（的长度）为止
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    }

    ///处理尾数特殊情况
    if ( i+length < N ) /* 归并最后2个子列*/ ///子列可能不是完整的length长度
        Merge( A, TmpA, i, i+length, N-1);
    else /* 最后只剩1个子列*/
        for ( j = i; j < N; j++ ) TmpA[j] = A[j];///直接把剩下的子列复制
}

void Merge_Sort( ElementType A[], int N )
{
    int length;  //length是本轮两两合并后的子序列的长度
    ElementType *TmpA;

    length = 1; /* 初始化子序列长度*/
    TmpA = malloc( N * sizeof( ElementType ) );
    if ( TmpA != NULL ) {
        while( length < N ) {
            ///子列 两两归并   ,互为临时数组，这样只需要开辟2个数组的空间，就能完成算法
            Merge_pass( A, TmpA, N, length );
            length *= 2;
            Merge_pass( TmpA, A, N, length );
            length *= 2;
        }
        free( TmpA );
    }
    else printf( "空间不足" );
}

