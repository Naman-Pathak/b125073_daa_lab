#include <stdio.h>

typedef struct
{
    int min;
    int max;
} MaxMin;

MaxMin findMaxMin(int arr[], int low, int high)
{
    MaxMin result, leftResult, rightResult;

    // Only one element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];

        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    int mid = (low + high) / 2;

    leftResult = findMaxMin(arr, low, mid);
    rightResult = findMaxMin(arr, mid + 1, high);

    // Find minimum
    if (leftResult.min < rightResult.min)
        result.min = leftResult.min;
    else
        result.min = rightResult.min;

    // Find maximum
    if (leftResult.max > rightResult.max)
        result.max = leftResult.max;
    else
        result.max = rightResult.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    MaxMin result = findMaxMin(arr, 0, n - 1);

    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);

    return 0;
}