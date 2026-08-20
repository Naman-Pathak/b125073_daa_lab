#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type;   // +1 = entry, -1 = exit
} Event;

/* Merge function for Merge Sort */
void merge(Event events[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;

    int size = right - left + 1;

    Event *temp = (Event *)malloc(size * sizeof(Event));

    while (i <= mid && j <= right) {
        if (events[i].time < events[j].time) {
            temp[k++] = events[i++];
        } else {
            temp[k++] = events[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = events[i++];
    }

    while (j <= right) {
        temp[k++] = events[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        events[i] = temp[k];
    }

    free(temp);
}

/* Merge Sort */
void mergeSort(Event events[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(events, left, mid);
        mergeSort(events, mid + 1, right);

        merge(events, left, mid, right);
    }
}

int main() {
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    printf("Enter entry and exit time for each person:\n");

    for (int i = 0; i < n; i++) {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = +1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events by time */
    mergeSort(events, 0, 2 * n - 1);

    int currentPeople = 0;
    int maxPeople = 0;
    int maxTime = 0;

    /* Scan sorted events */
    for (int i = 0; i < 2 * n; i++) {

        if (events[i].type == +1) {
            currentPeople++;

            if (currentPeople > maxPeople) {
                maxPeople = currentPeople;
                maxTime = events[i].time;
            }
        } else {
            currentPeople--;
        }
    }

    printf("\nMaximum number of people present = %d\n", maxPeople);
    printf("Time when maximum was reached = %d\n", maxTime);

    free(events);

    return 0;
}