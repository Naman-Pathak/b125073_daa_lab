#include <stdio.h>
#include <stdlib.h>

long long totalCost = 0;
long long reversalCount = 0;

void reverseRange(int a[], int left, int right) {
    if (left >= right)
        return;

    totalCost += right - left + 1;
    reversalCount++;

    while (left < right) {
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;

        left++;
        right--;
    }
}

int stablePartition(int a[], int left, int right, int valueMid) {
    if (left > right)
        return 0;

    if (left == right)
        return a[left] <= valueMid;

    int middle = left + (right - left) / 2;

    int leftLowCount =
        stablePartition(a, left, middle, valueMid);

    int rightLowCount =
        stablePartition(a, middle + 1, right, valueMid);

    int highLeftStart = left + leftLowCount;
    int highLeftEnd = middle;

    int lowRightStart = middle + 1;
    int lowRightEnd = middle + rightLowCount;

    if (highLeftStart <= highLeftEnd &&
        lowRightStart <= lowRightEnd) {

        reverseRange(a, highLeftStart, highLeftEnd);
        reverseRange(a, lowRightStart, lowRightEnd);
        reverseRange(a, highLeftStart, lowRightEnd);
    }

    return leftLowCount + rightLowCount;
}

void reversalSort(int a[],
                  int left,
                  int right,
                  int lowValue,
                  int highValue) {

    if (left >= right || lowValue >= highValue)
        return;

    int middleValue =
        lowValue + (highValue - lowValue) / 2;

    int lowCount =
        stablePartition(a, left, right, middleValue);

    reversalSort(
        a,
        left,
        left + lowCount - 1,
        lowValue,
        middleValue
    );

    reversalSort(
        a,
        left + lowCount,
        right,
        middleValue + 1,
        highValue
    );
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *p = malloc(n * sizeof(int));

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    reversalSort(p, 0, n - 1, 1, n);

    printf("Sorted permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    printf("Number of reversals = %lld\n", reversalCount);
    printf("Total reversal cost = %lld\n", totalCost);

    free(p);

    return 0;
}