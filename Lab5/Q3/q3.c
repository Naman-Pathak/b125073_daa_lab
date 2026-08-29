#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if(low < high) {
        int pi = partition(a, low, high);

        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    FILE *fp = fopen("numbers.txt", "w");

    srand(time(NULL));

    for(int i = 0; i < n; i++)
        fprintf(fp, "%d ", rand() % 1000);

    fclose(fp);

    int a[n];

    fp = fopen("numbers.txt", "r");

    for(int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    quickSort(a, 0, n - 1);

    fp = fopen("sorted.txt", "w");

    for(int i = 0; i < n; i++)
        fprintf(fp, "%d ", a[i]);

    fclose(fp);
    printf("Sorting completed. Output stored in sorted.txt\n");

    return 0;
}