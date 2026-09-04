#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int a[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

void copyArray(int source[], int destination[], int n) {
    for (int i = 0; i < n; i++)
        destination[i] = source[i];
}

int maximum(int a[], int n) {
    int max = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

void firstSecondLargest(int a[], int n) {
    if (n < 2) {
        printf("At least two elements are required.\n");
        return;
    }

    int first = a[0];
    int second = 0;
    int secondExists = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] > first) {
            second = first;
            first = a[i];
            secondExists = 1;
        } else if (a[i] < first) {
            if (!secondExists || a[i] > second) {
                second = a[i];
                secondExists = 1;
            }
        }
    }

    printf("Largest element = %d\n", first);

    if (secondExists)
        printf("Second largest element = %d\n", second);
    else
        printf("Distinct second largest element does not exist.\n");
}

double mean(int a[], int n) {
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum / n;
}

double median(int a[], int n) {
    int *temp = malloc(n * sizeof(int));

    copyArray(a, temp, n);
    mergeSort(temp, 0, n - 1);

    double result;

    if (n % 2 == 1)
        result = temp[n / 2];
    else
        result = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;

    free(temp);

    return result;
}

double standardDeviation(int a[], int n) {
    double avg = mean(a, n);
    double sum = 0;

    for (int i = 0; i < n; i++) {
        double difference = a[i] - avg;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}

void mode(int a[], int n) {
    int *temp = malloc(n * sizeof(int));

    copyArray(a, temp, n);
    mergeSort(temp, 0, n - 1);

    int modeValue = temp[0];
    int maxCount = 1;

    int currentValue = temp[0];
    int currentCount = 1;

    for (int i = 1; i < n; i++) {
        if (temp[i] == currentValue) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                modeValue = currentValue;
            }

            currentValue = temp[i];
            currentCount = 1;
        }
    }

    if (currentCount > maxCount) {
        maxCount = currentCount;
        modeValue = currentValue;
    }

    if (maxCount == 1)
        printf("No mode exists.\n");
    else
        printf("Mode = %d, frequency = %d\n", modeValue, maxCount);

    free(temp);
}

void removeDuplicates(int a[], int n) {
    int *temp = malloc(n * sizeof(int));

    copyArray(a, temp, n);
    mergeSort(temp, 0, n - 1);

    printf("Array after removing duplicates: ");

    printf("%d ", temp[0]);

    for (int i = 1; i < n; i++) {
        if (temp[i] != temp[i - 1])
            printf("%d ", temp[i]);
    }

    printf("\n");

    free(temp);
}

void reverseArray(int a[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

void partitionAroundPivot(int a[], int n, int pivot) {
    int *temp = malloc(n * sizeof(int));
    int index = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] >= pivot)
            temp[index++] = a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < pivot)
            temp[index++] = a[i];
    }

    printf("Partitioned array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", temp[i]);

    printf("\n");

    free(temp);
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int *a = malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nMaximum element = %d\n", maximum(a, n));

    firstSecondLargest(a, n);

    printf("Mean = %.2f\n", mean(a, n));

    printf("Median = %.2f\n", median(a, n));

    printf("Standard deviation = %.2f\n", standardDeviation(a, n));

    mode(a, n);

    removeDuplicates(a, n);

    int *reversed = malloc(n * sizeof(int));

    copyArray(a, reversed, n);
    reverseArray(reversed, n);
    printf("Reversed array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", reversed[i]);
    printf("\n");
    int pivot;
    printf("Enter pivot value: ");
    scanf("%d", &pivot);
    partitionAroundPivot(a, n, pivot);
    free(reversed);
    free(a);
    return 0;
}