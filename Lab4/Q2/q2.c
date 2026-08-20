#include <stdio.h>

// Merge two sorted parts
void merge(int arr[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;

    int temp[right - left + 1];

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

// Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Binary Search
int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

int main() {
    int n, x;

    printf("Enter size of each set: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter x: ");
    scanf("%d", &x);

    // Sort S2
    mergeSort(S2, 0, n - 1);

    // Check every element of S1
    for (int i = 0; i < n; i++) {
        int required = x - S1[i];

        if (binarySearch(S2, n, required)) {
            printf("Pair exists: (%d, %d)\n",
                   S1[i], required);
            return 0;
        }
    }

    printf("No such pair exists.\n");

    return 0;
}