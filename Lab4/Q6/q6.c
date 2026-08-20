#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int point;
    int type;       // +1 = start, -1 = end
} Event;
/* Merge two sorted parts */
void merge(Event events[], int left, int mid, int right){
    int i = left;
    int j = mid + 1;
    int k = 0;

    int size = right - left + 1;

    Event *temp = malloc(size * sizeof(Event));

    while (i <= mid && j <= right){
        /*
         * Sort primarily by point.
         *
         * If points are equal, START (+1) comes
         * before END (-1).
         */
        if (events[i].point < events[j].point ||
            (events[i].point == events[j].point &&
             events[i].type > events[j].type))
        {
            temp[k++] = events[i++];
        }
        else
        {
            temp[k++] = events[j++];
        }
    }

    while (i <= mid)
        temp[k++] = events[i++];

    while (j <= right)
        temp[k++] = events[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        events[i] = temp[k];

    free(temp);
}


/* Merge Sort */
void mergeSort(Event events[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(events, left, mid);
        mergeSort(events, mid + 1, right);

        merge(events, left, mid, right);
    }
}
int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    printf("Enter left and right endpoints:\n");

    for (int i = 0; i < n; i++)
    {
        int left, right;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &left, &right);

        // Start event
        events[2 * i].point = left;
        events[2 * i].type = +1;

        // End event
        events[2 * i + 1].point = right;
        events[2 * i + 1].type = -1;
    }


    /* Sort all events */
    mergeSort(events, 0, 2 * n - 1);


    int currentCount = 0;
    int maxCount = 0;
    int maxPoint = 0;


    /* Sweep through all events */
    for (int i = 0; i < 2 * n; i++){
        if (events[i].type == +1){
            currentCount++;

            /*
             * The current point is inside this many
             * intervals.
             */
            if (currentCount > maxCount) {
                maxCount = currentCount;
                maxPoint = events[i].point;
            }
        }
        else{
            currentCount--;
        }
    }
    printf("\nPoint with maximum overlap = %d\n", maxPoint);
    printf("Maximum number of intervals = %d\n", maxCount);
    free(events);
    return 0;
}