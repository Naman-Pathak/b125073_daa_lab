#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
void swap(ll *a, ll *b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void insert(ll heap[], int *size, ll value) {
    int i = (*size)++;
    heap[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] <= heap[i])
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

ll extractMin(ll heap[], int *size) {
    ll result = heap[0];

    (*size)--;

    if (*size > 0) {
        heap[0] = heap[*size];

        int i = 0;

        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < *size &&
                heap[left] < heap[smallest])
                smallest = left;

            if (right < *size &&
                heap[right] < heap[smallest])
                smallest = right;

            if (smallest == i)
                break;

            swap(&heap[i], &heap[smallest]);
            i = smallest;
        }
    }

    return result;
}

int main(void) {
    int n;

    printf("Enter number of sticks: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    ll *heap = malloc((size_t)n * sizeof(ll));

    if (heap == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int size = 0;

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {
        ll length;

        if (scanf("%lld", &length) != 1 || length < 0) {
            printf("Invalid stick length.\n");
            free(heap);
            return 1;
        }

        insert(heap, &size, length);
    }

    ll totalCost = 0;

    while (size > 1) {
        ll x = extractMin(heap, &size);
        ll y = extractMin(heap, &size);

        ll cost = x + y;
        totalCost += cost;

        insert(heap, &size, cost);
    }

    printf("Minimum total cost = %lld\n", totalCost);

    free(heap);
    return 0;
}
