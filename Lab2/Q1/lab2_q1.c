#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

int arr[MAX];

double getTime()
{
    return (double)clock() / CLOCKS_PER_SEC;
}

void search(int n, int key)
{
    for(int i = 0; i < n; i++)
        if(arr[i] == key)
            return;
}

void minimum(int n)
{
    int min = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] < min)
            min = arr[i];
}

void maximum(int n)
{
    int max = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] > max)
            max = arr[i];
}

int main()
{
    FILE *fp = fopen("result.csv", "w");

    fprintf(fp,"N,Search,Minimum,Maximum\n");

    srand(time(NULL));

    for(int n = 1000; n <= 100000; n += 5000)
    {
        for(int i = 0; i < n; i++)
            arr[i] = rand();

        double start,end;

        start = getTime();
        search(n,-1);
        end = getTime();
        double searchTime = end-start;

        start = getTime();
        minimum(n);
        end = getTime();
        double minTime = end-start;

        start = getTime();
        maximum(n);
        end = getTime();
        double maxTime = end-start;

        fprintf(fp,"%d,%lf,%lf,%lf\n",
                n,
                searchTime,
                minTime,
                maxTime);

        printf("%d Done\n",n);
    }

    fclose(fp);

    printf("Data saved to result.csv\n");

    return 0;
}