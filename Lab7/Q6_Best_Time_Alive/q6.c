#include <stdio.h>
#include <stdlib.h>

/*
   Sweep-line with a DP/prefix recurrence.

   Each person contributes two events:
     birth year  -> +1
     death year  -> -1

   For equal years, deaths are processed before births, as required by the lab.
   After sorting, active[i] is the number of scientists alive after event i:
       active[i] = active[i-1] + event[i].delta
*/

typedef struct {
    int year;
    int delta; /* -1 = death, +1 = birth */
} Event;

int cmp_event(const void *a, const void *b) {
    const Event *x = (const Event *)a;
    const Event *y = (const Event *)b;

    if (x->year != y->year)
        return (x->year > y->year) - (x->year < y->year);

    /* Death first when the years are equal. */
    if (x->delta != y->delta)
        return (x->delta < y->delta) ? -1 : 1;

    return 0;
}

int main(void) {
    int n;

    printf("Enter number of scientists: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Event *events = (Event *)malloc((2 * n) * sizeof(Event));
    if (!events) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter birth year and death year for each scientist:\n");
    for (int i = 0; i < n; ++i) {
        int birth, death;
        if (scanf("%d %d", &birth, &death) != 2 || birth > death) {
            printf("Invalid birth/death data.\n");
            free(events);
            return 1;
        }
        events[2 * i].year = birth;
        events[2 * i].delta = +1;
        events[2 * i + 1].year = death;
        events[2 * i + 1].delta = -1;
    }

    qsort(events, 2 * n, sizeof(Event), cmp_event);

    int active = 0;
    int best = -1;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; ++i) {
        active += events[i].delta;

        if (active > best) {
            best = active;
            bestYear = events[i].year;
        }
    }

    printf("Largest number of scientists alive = %d\n", best);
    printf("A year when this maximum occurs = %d\n", bestYear);

    free(events);
    return 0;
}
