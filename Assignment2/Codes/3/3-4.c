#include<stdio.h>

int max_subsquence_sum(int a[], unsigned int n)
{
    int this_sum, max_sum, best_i, best_j, i, j;
    i = this_sum = max_sum = 0;
    best_i = best_j = -1;
    for(j = 0; j < n; ++j)
    {
        this_sum += a[j];
        if(this_sum > max_sum)
        {
            max_sum = this_sum;
            best_i = i;
            best_j = j;
        }
        else if(this_sum < 0)
        {
            i = j + 1;
            this_sum = 0;
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
    int a[] = {4, -6, 5, -2, -5, 2, 6, -2};
    printf("The max sum is: %d", max_subsquence_sum(a, 8));
    return 0;
}