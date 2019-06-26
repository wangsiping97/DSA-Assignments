#include<stdio.h>

int max3(int a, int b, int c)
{
    if(a >= b)
    {
        if(a >= c) return(a);
        else return(c);
    }
    else if(c >= b) return(c);
    else return(b);
}

static int maxSubSum(int A[], int left, int right)
{
    int MaxLeftSum = 0, MaxRightSum = 0; 
    int MaxLeftBorderSum = 0, MaxRightBorderSum = 0;
    int LeftBorderSum = 0, RightBorderSum = 0;
    int center = (left + right) / 2, i;
    
    if(left == right)
    {
        if(A[left] > 0)
            return A[left];
        
        else
            return 0;
    }

    MaxLeftSum = maxSubSum(A, left, center);
    MaxRightSum = maxSubSum(A, center + 1, right);
    for(i = center; i >= left; i--)
    {
        LeftBorderSum += A[i];
        if(LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    for(i = center + 1; i <= right; i++)
    {
        RightBorderSum += A[i];
        if(RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    
    return(max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum));
}

int main()
{
    int a[] = {4, -3, 5, -2, -1, 2, 6, -2};
    printf("The max sum is: %d", maxSubSum(a, 0, 7));
    return 0;
}