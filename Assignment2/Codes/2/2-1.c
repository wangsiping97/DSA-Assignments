#include<stdio.h>
#include<time.h>

int main()
{
    int Sum; long int N, i;

    while(1)
    {
        printf("\n N = ");
        scanf("%ld", &N);
        if(N == -1) break;
        clock_t start_time, end_time;
        start_time = clock();

        Sum = 0;
        for(i = 0; i < N; i++)
            Sum++;

        end_time = clock();
        printf(" Running time = %f s\n\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);
    }

    return 0;
}
// 50000000