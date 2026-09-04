#include <stdio.h>
#include<stdlib.h>
int main()
{
    int n, i;
    printf("Enter n: ");
    scanf("%d", &n);
    int *fib = (int*) malloc(n*sizeof(int));
    if (n < 0)
    {
        printf("Invalid input\n");
        return 0;
    }
    fib[0] = 0;
    if (n >= 1)
        fib[1] = 1;

    for (i = 2; i <= n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    printf("The %dth Fibonacci number is %d\n", n, fib[n]);
    return 0;
}