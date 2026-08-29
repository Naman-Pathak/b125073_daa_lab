#include <stdio.h>
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
int quickSelect(int a[], int low, int high, int k) {
    if(low <= high) {
        int pi = partition(a, low, high);
        if(pi == k) return a[pi];
        else if(pi > k) return quickSelect(a, low, pi - 1, k);
        else return quickSelect(a, pi + 1, high, k);
    }
    return -1;
}
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if(n % 2 != 0) {
        printf("Median = %d\n", quickSelect(a, 0, n - 1, n / 2));
    } else {
        int m1 = quickSelect(a, 0, n - 1, n / 2 - 1);
        int m2 = quickSelect(a, 0, n - 1, n / 2);
        printf("Median = %.2f\n", (m1 + m2) / 2.0);
    }

    return 0;
}