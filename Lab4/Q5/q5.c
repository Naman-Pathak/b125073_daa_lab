#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int start;
    int end;
} Interval;

/* Merge function for Merge Sort */
void merge(Interval a[], int left, int mid, int right){
    int i = left;
    int j = mid + 1;
    int k = 0;

    int size = right - left + 1;
    Interval *temp = malloc(size * sizeof(Interval));

    while (i <= mid && j <= right)
    {
        if (a[i].start <= a[j].start)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        a[i] = temp[k];

    free(temp);
}

/* Merge Sort */
void mergeSort(Interval a[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

/* Merge overlapping intervals */
int mergeIntervals(Interval a[], int n, Interval result[])
{
    if (n == 0)
        return 0;

    int count = 0;

    // Start with the first interval
    int currentStart = a[0].start;
    int currentEnd = a[0].end;

    for (int i = 1; i < n; i++)
    {
        /*
         * Overlap exists if the next interval starts
         * before or at the end of the current interval.
         */
        if (a[i].start <= currentEnd)
        {
            // Extend the current interval if necessary
            if (a[i].end > currentEnd)
                currentEnd = a[i].end;
        }
        else
        {
            // No overlap, store current interval
            result[count].start = currentStart;
            result[count].end = currentEnd;
            count++;

            // Start a new interval
            currentStart = a[i].start;
            currentEnd = a[i].end;
        }
    }

    // Store the final interval
    result[count].start = currentStart;
    result[count].end = currentEnd;
    count++;

    return count;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval *a = malloc(n * sizeof(Interval));
    Interval *result = malloc(n * sizeof(Interval));

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &a[i].start, &a[i].end);
    }

    /* Sort intervals by starting point */
    mergeSort(a, 0, n - 1);

    /* Merge overlapping intervals */
    int count = mergeIntervals(a, n, result);

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++){
        printf("(%d,%d) ", result[i].start, result[i].end);
    }

    printf("\n");

    free(a);
    free(result);
    return 0;
}