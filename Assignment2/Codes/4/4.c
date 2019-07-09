#include<stdio.h>
#define NOT_FOUND -1

int binary_search(int a[], int x, unsigned int n)
{
    int low, mid, high;
    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low + high)/2;
        if(a[mid] < x)
            low = mid + 1;
        else if(a[mid] > x)
            high = mid - 1;
        else
            return(mid);  
    }
    return(NOT_FOUND);
}

int main()
{
    int a[] = {7, 14, 18, 21, 23, 29, 31, 35, 38, 42, 46, 49, 52};
    int aim = 14;
    if(binary_search(a, aim, 13) != -1)
        printf("The aim is a[%d].", binary_search(a, aim, 13));
    else
        printf("Can not find the aim in the array.");
    return 0;
}