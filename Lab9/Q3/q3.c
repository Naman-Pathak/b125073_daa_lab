#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int distance;
    int fuel;
} Station;

/* ---------- Swap ---------- */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ---------- Max Heap ---------- */

void insertHeap(int heap[], int *size, int value)
{
    int i = *size;

    heap[*size] = value;
    (*size)++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        swap(&heap[parent], &heap[i]);

        i = parent;
    }
}

int extractMax(int heap[], int *size)
{
    int maxValue = heap[0];

    heap[0] = heap[*size - 1];
    (*size)--;

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < *size &&
            heap[left] > heap[largest])
        {
            largest = left;
        }

        if (right < *size &&
            heap[right] > heap[largest])
        {
            largest = right;
        }

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return maxValue;
}

/* ---------- Compare Stations ---------- */

int compareStations(const void *a, const void *b)
{
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;

    return s1->distance - s2->distance;
}

/* ---------- Minimum Stops ---------- */

int minimumStops(int D, int F,
                 Station stations[], int n)
{
    /*
       Sort stations by distance.
    */
    qsort(stations, n, sizeof(Station),
          compareStations);

    /*
       Max heap containing fuel amounts
       of reachable stations.
    */
    int *heap = (int *)malloc(n * sizeof(int));

    if (heap == NULL)
        return -1;

    int heapSize = 0;
    int index = 0;

    int reach = F;
    int stops = 0;

    while (reach < D)
    {
        /*
           Add all stations that can currently
           be reached.
        */
        while (index < n &&
               stations[index].distance <= reach)
        {
            insertHeap(heap,
                        &heapSize,
                        stations[index].fuel);

            index++;
        }

        /*
           No reachable station means
           destination is impossible.
        */
        if (heapSize == 0)
        {
            free(heap);
            return -1;
        }

        /*
           Take the station with maximum fuel.
        */
        int maximumFuel =
            extractMax(heap, &heapSize);

        reach += maximumFuel;
        stops++;
    }

    free(heap);

    return stops;
}
int main()
{
    int D, F, n;

    printf("Enter target distance D: ");
    scanf("%d", &D);

    printf("Enter initial fuel F: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    Station *stations =
        (Station *)malloc(n * sizeof(Station));

    if (stations == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter station details:\n");
    printf("Distance Fuel\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",
              &stations[i].distance,
              &stations[i].fuel);
    }

    int answer =
        minimumStops(D, F, stations, n);

    if (answer == -1)
    {
        printf("\nDestination cannot be reached.\n");
    }
    else
    {
        printf("\nMinimum refuelling stops = %d\n",
               answer);
    }
    free(stations);

    return 0;
}