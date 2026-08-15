#include <stdio.h>

// Binary Search
int binarySearch(int arr[], int n, int x){
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Ternary Search
int ternarySearch(int arr[], int n, int x){
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        if (arr[mid1] == x)
            return mid1;

        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (x > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main(){
    int n, x;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter sorted elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &x);

    int b = binarySearch(arr, n, x);
    int t = ternarySearch(arr, n, x);

    if (b != -1)
        printf("\nBinary Search: Element found at index %d\n", b);
    else
        printf("\nBinary Search: Element not found\n");

    if (t != -1)
        printf("Ternary Search: Element found at index %d\n", t);
    else
        printf("Ternary Search: Element not found\n");

    printf("\nTime Complexity:\n");
    printf("Binary Search: O(log2 n)\n");
    printf("Ternary Search: O(log3 n)\n");

    return 0;
}