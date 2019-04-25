#include<stdio.h>

int max_subsquence_sum(int a[], unsigned int n)
{
    int this_sum, max_sum, best_i, best_j, i, j, k;
    max_sum = 0;
    best_i = best_j = -1;
    for(i = 0; i < n; ++i)
    {
        this_sum = 0;
        for(j = i; j < n; ++j)
        {
            this_sum += a[j];
            if(this_sum > max_sum)
            {
                max_sum = this_sum;
                best_i = i;
                best_j = j;
            }
        }

    }

    printf("The sub-sequence is: (");
    for(int s = best_i; s < best_j; ++s)
    {
        printf("%d, ", a[s]);
    }
    printf("%d)\n", a[best_j]);
    
    return(max_sum);
}

int main()
{
    int a[] = {-2, 11, -5, 13, -4};
    printf("The max sum is: %d", max_subsquence_sum(a, 5));
    return 0;
}