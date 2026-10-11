#include <stdio.h>
#define MAX 1000

long long heap[MAX];
int size = 0;

void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void insert(long long x) {
    int i = size++;
    heap[i] = x;

    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

long long extractMax() {
    long long maxValue = heap[0];
    heap[0] = heap[--size];

    int i = 0;

    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return maxValue;
}

long long minimiseDeviation(long long a[], int n) {
    long long currentMin = a[0];

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0)
            a[i] *= 2;

        insert(a[i]);

        if (a[i] < currentMin)
            currentMin = a[i];
    }

    long long best = heap[0] - currentMin;

    while (size > 0) {
        long long x = extractMax();

        if (x - currentMin < best)
            best = x - currentMin;

        if (x % 2 != 0)
            break;

        x /= 2;

        if (x < currentMin)
            currentMin = x;

        insert(x);

        long long deviation = heap[0] - currentMin;

        if (deviation < best)
            best = deviation;
    }

    return best;
}

int main() {
    int n;
    long long a[MAX];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);

        if (a[i] <= 0) {
            printf("Elements must be positive.\n");
            return 1;
        }
    }

    printf("Minimum deviation = %lld\n",
           minimiseDeviation(a, n));

    return 0;
}
