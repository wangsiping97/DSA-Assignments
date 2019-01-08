// Write the recursive version and the iterative version of Fibonacci(100), 
// and output the running times of the two programs.
// This 1-1 program is for the recursive version of Fibonacci(100). 

#include<stdio.h>
#include<time.h>

long int Fibonacci(int n)
{
    if(n == 1 || n == 2)
    {
        return 1;
    }
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main()
{
    long result;
    int i = 100;
    clock_t start_time, end_time;
    start_time = clock();
    result = Fibonacci(i);
    end_time = clock();
    printf("Fibonacci(%d) = %ld\n", i, result);
    printf("The time consumption is %f s.\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);
    return 0;
}
