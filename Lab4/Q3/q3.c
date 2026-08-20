#include <stdio.h>
#include <stdlib.h>
/* ---------- Merge Sort ---------- */
void merge(int a[], int left, int mid, int right){
    int i = left;
    int j = mid + 1;
    int k = 0;

    int size = right - left + 1;
    int *temp = (int *)malloc(size * sizeof(int));

    while (i <= mid && j <= right){
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];

    while (j <= right) temp[k++] = a[j++];

    for (i = left, k = 0; i <= right; i++, k++) a[i] = temp[k];
    free(temp);
}

void mergeSort(int a[], int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}
/* ---------- Binary Search ---------- */
int binarySearch(int a[], int left, int right, long long target){
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (a[mid] == target) return 1;
        if (a[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}
/*
   Choose k-1 elements.
   The kth element is found using binary search.
*/
int kSum(int a[], int n, int k, int T,
         int start, int chosen, long long sum){
    /*
       We have selected k-1 elements.
       Now find the required kth element.
    */
    if (chosen == k - 1){
        long long required = (long long)T - sum;
        return binarySearch(a, start, n - 1, required);
    }

    /*
       Choose the next element.
    */
    for (int i = start; i < n; i++)
    {
        if (kSum(a, n, k, T,
                 i + 1,
                 chosen + 1,
                 sum + a[i]))
        {
            return 1;
        }
    }

    return 0;
}

/* ---------- Main Function ---------- */

int main()
{
    int n, k, T;

    printf("Enter n: ");
    scanf("%d", &n);

    int *S = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    if (k < 2 || k > n)
    {
        printf("Invalid value of k.\n");
        free(S);
        return 0;
    }

    /* Sort the set */
    mergeSort(S, 0, n - 1);

    /* Check for k elements whose sum is T */
    if (kSum(S, n, k, T, 0, 0, 0))
    {
        printf("Yes, %d elements add up to %d.\n", k, T);
    }
    else
    {
        printf("No, %d elements do not add up to %d.\n", k, T);
    }

    free(S);

    return 0;
}