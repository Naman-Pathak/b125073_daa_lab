#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
   Q5: Hitting a moving target.

   We use a DP over the set of target positions that are still possible.
   possible[p] is true when the target can be at hiding spot p immediately
   before a shot.

   After a missed shot at s:
     1) remove s from the possible set;
     2) the target moves to an adjacent position for the next shot.

   A constructive guaranteed strategy is:
     n = 2: 1, 1
     n odd : 2,3,...,n-1, 2,3,...,n-1
     n even: 2,3,...,n-1, n-1,n-2,...,2

   The program generates this schedule and validates it using DP.
*/

static void print_schedule(const int *shots, int m) {
    printf("Shots: ");
    for (int i = 0; i < m; ++i) {
        printf("%d", shots[i]);
        if (i + 1 < m) printf(" ");
    }
    printf("\n");
}

static bool validate_schedule(int n, const int *shots, int m) {
    bool *possible = (bool *)malloc((n + 1) * sizeof(bool));
    bool *next = (bool *)malloc((n + 1) * sizeof(bool));
    if (!possible || !next) {
        free(possible);
        free(next);
        return false;
    }

    for (int i = 1; i <= n; ++i) possible[i] = true;

    for (int t = 0; t < m; ++t) {
        int s = shots[t];
        if (s < 1 || s > n) {
            free(possible);
            free(next);
            return false;
        }

        possible[s] = false;  /* Any target here would be hit. */

        bool empty = true;
        for (int i = 1; i <= n; ++i) {
            if (possible[i]) {
                empty = false;
                break;
            }
        }
        if (empty) {
            free(possible);
            free(next);
            return true;
        }

        for (int i = 1; i <= n; ++i) next[i] = false;

        /* Target moves exactly one adjacent spot before the next shot. */
        for (int i = 1; i <= n; ++i) {
            if (!possible[i]) continue;
            if (i > 1) next[i - 1] = true;
            if (i < n) next[i + 1] = true;
        }

        for (int i = 1; i <= n; ++i) possible[i] = next[i];
    }

    free(possible);
    free(next);
    return false;
}

int main(void) {
    int n;

    printf("Enter number of hiding spots n (>1): ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int m = (n == 2) ? 2 : 2 * (n - 2);
    int *shots = (int *)malloc((m + 1) * sizeof(int));
    if (!shots) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int idx = 0;
    if (n == 2) {
        shots[idx++] = 1;
        shots[idx++] = 1;
    } else if (n % 2 == 1) {
        for (int s = 2; s <= n - 1; ++s) shots[idx++] = s;
        for (int s = 2; s <= n - 1; ++s) shots[idx++] = s;
    } else {
        for (int s = 2; s <= n - 1; ++s) shots[idx++] = s;
        for (int s = n - 1; s >= 2; --s) shots[idx++] = s;
    }

    print_schedule(shots, m);
    printf("Guaranteed hit: %s\n", validate_schedule(n, shots, m) ? "YES" : "NO");
    printf("Number of shots in this strategy = %d\n", m);

    free(shots);
    return 0;
}
