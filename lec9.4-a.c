//有序子列的归并算法



void Merge(ElementType A[],ELementType TmpA[],int L ,int R,int RightEnd)
{
    //L=左边起始位置，R=右边起始位置，RightEnd=右边终点位置
    LeftEnd = R-1;  //LeftEnd终点位置，假设左右两列存储上紧邻
    Tmp = L;    //Tmp存放结果的数组的初始位置
    NumElements = RightEnd - L +1;
    while(L<= LeftEnd && R <=RightEnd){
        if(A[L]<= A[R])
            TmpA[Tmp++] =A[L++];
        else
            TmpA[Tmp++]=A[R++];
    }

    //此时L的位置就是 两个子序列有重叠的数量

    //把剩下的子序列直接合并到结果数组中
    while(L<=LeftEnd)   //左边子序列有剩下，直接复制到结果数组中
        TmpA[Tmp++] = A[L++];
    while (R<=RightEnd)
        TmpA[Tmp++]=A[R++];

    //因为要返回数组A[]，而结果在TmpA[]数组里，所以复制过去
    for (int i = 0; i < NumElements;i++,RightEnd--) {
        A[RightEnd] = TmpA[RightEnd];
    }
}

