// Write the recursive version and the iterative version of Fibonacci(100), 
// and output the running times of the two programs.
// This 1-2 program is for the iterative version of Fibonacci(100). 

#include<stdio.h>
#include<time.h>

int main()
{
    long f_1 = 1, f_2 = 1, f_n = 0;
    clock_t start_time, end_time;
    start_time = clock();
    for(int i = 3; i <= 100; ++ i)
    {
        f_n = f_1 + f_2;
        f_1 = f_2;
        f_2 = f_n;
    }
    end_time = clock();
    printf("Fibonacci(100) = %ld\n", f_n);
    printf("The time consumption is %f s.\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);
    return 0;
}