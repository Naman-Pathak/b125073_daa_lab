#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int start;
    int end;
} Meeting;

int compare(const void *a, const void *b) {
    Meeting *m1 = (Meeting *)a;
    Meeting *m2 = (Meeting *)b;

    if (m1->start < m2->start)
        return -1;
    if (m1->start > m2->start)
        return 1;
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertMin(int heap[], int *size, int value) {
    int i = (*size)++;
    heap[i] = value;

    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int removeMin(int heap[], int *size) {
    int result = heap[0];
    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < *size && heap[left] < heap[smallest])
            smallest = left;

        if (right < *size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int minMeetingRooms(Meeting meetings[], int n) {
    if (n == 0)
        return 0;

    qsort(meetings, n, sizeof(Meeting), compare);

    int heap[MAX];
    int size = 0;
    int maxRooms = 0;

    for (int i = 0; i < n; i++) {
        if (size > 0 && heap[0] <= meetings[i].start) {
            removeMin(heap, &size);
        }

        insertMin(heap, &size, meetings[i].end);

        if (size > maxRooms)
            maxRooms = size;
    }

    return maxRooms;
}

int main(void) {
    Meeting meetings[MAX];
    int n;

    printf("Enter number of meetings: ");

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    printf("Enter start and end time of each meeting:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d",
                  &meetings[i].start,
                  &meetings[i].end) != 2 ||
            meetings[i].start > meetings[i].end) {
            printf("Invalid meeting interval.\n");
            return 1;
        }
    }

    printf("Minimum number of meeting rooms = %d\n",
           minMeetingRooms(meetings, n));

    return 0;
}