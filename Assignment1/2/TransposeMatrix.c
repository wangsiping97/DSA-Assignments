// Write functions to implement the following purposes:
// 1) Construct a 3×3 matrix stored in a 2-dimensional array in main() function.
// 2) Call a function to transpose the matrix with a pointer parameter as the
// function’s parameter.
// 3) Output the transposed matrix in main() function.

#include<stdio.h>
#include<stdlib.h>

void transpose(int **p)
{
    int t;
    for(int i = 0; i < 3; ++ i)
    {
        for(int j = 0; j < i; ++ j)
        {
            t = *(*(p + i) + j);
            *(*(p + i) + j) = *(*(p + j) + i);
            *(*(p + j) + i) = t;
        }
    }
}

int main()
{
    int ar[3][3];
    int i, j;
    printf("Please input 9 numbers: \n");
    for(int i = 0; i < 3; ++ i)
    {
        for(int j = 0; j < 3; ++j)
            scanf("%d", &ar[i][j]);
    }

    int **a = (int **)malloc(3 * sizeof(int *)); 
    for(i = 0; i < 3; ++ i)
    {
        a[i] = (int *)malloc(3 * sizeof(int)); 
        for(j = 0; j < 3; ++ j)
            a[i][j] = ar[i][j];
    }

    transpose(a);

    printf("The transposed matrix: \n");
    for(i = 0; i < 3; ++ i)
    {
        for(j = 0; j < 3; ++j)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    return 0;
}