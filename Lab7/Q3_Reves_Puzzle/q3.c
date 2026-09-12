#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Four-peg Reve's puzzle using the standard Frame-Stewart DP recurrence.

   dp[n] = minimum moves for n disks with four pegs.

   Choose k smallest disks to move aside using four pegs,
   move the remaining n-k disks using the ordinary 3-peg Hanoi,
   then move the k disks onto the destination using four pegs.

   dp[n] = min_k (2*dp[k] + 2^(n-k) - 1)
*/

unsigned long long hanoi3(int n, int from, int to, int aux) {
    if (n == 0) return 0ULL;
    return 1ULL + hanoi3(n - 1, from, aux, to)
                 + hanoi3(n - 1, aux, to, from);
}

void print_hanoi3(int n, char from, char to, char aux) {
    if (n == 0) return;
    print_hanoi3(n - 1, from, aux, to);
    printf("Move disk from %c -> %c\n", from, to);
    print_hanoi3(n - 1, aux, to, from);
}

void print_fs(int n, char from, char to, char aux1, char aux2,
              int *bestSplit) {
    if (n == 0) return;
    if (n == 1) {
        printf("Move disk from %c -> %c\n", from, to);
        return;
    }

    int k = bestSplit[n];

    /* Move k smallest disks to aux1 using all four pegs. */
    print_fs(k, from, aux1, to, aux2, bestSplit);

    /* Move remaining n-k disks with classical 3-peg Hanoi. */
    print_hanoi3(n - k, from, to, aux2);

    /* Move k smallest disks from aux1 to destination using four pegs. */
    print_fs(k, aux1, to, from, aux2, bestSplit);
}

int main(void) {
    int n;

    printf("Enter number of disks n (1..30 recommended): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 30) {
        printf("Invalid input.\n");
        return 1;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    int *bestSplit = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL || bestSplit == NULL) {
        printf("Memory allocation failed.\n");
        free(dp);
        free(bestSplit);
        return 1;
    }

    dp[0] = 0ULL;
    bestSplit[0] = 0;
    if (n >= 1) {
        dp[1] = 1ULL;
        bestSplit[1] = 1;
    }

    for (int disks = 2; disks <= n; ++disks) {
        dp[disks] = ULLONG_MAX;
        unsigned long long pow2 = 1ULL;

        /* Need 2^(disks-k), so start with exponent disks-1 for k=1. */
        for (int k = 1; k < disks; ++k) {
            /* Compute 2^(disks-k) safely. */
            pow2 = 1ULL << (disks - k);
            unsigned long long candidate = 2ULL * dp[k] + pow2 - 1ULL;
            if (candidate < dp[disks]) {
                dp[disks] = candidate;
                bestSplit[disks] = k;
            }
        }
    }

    printf("Minimum moves = %llu\n", dp[n]);
    printf("Best split k = %d\n", bestSplit[n]);

    if (n == 8) {
        printf("For 8 disks, the DP gives 33 moves.\n");
        printf("\nOne optimal Frame-Stewart move sequence:\n");
        print_fs(n, 'A', 'D', 'B', 'C', bestSplit);
    }

    free(dp);
    free(bestSplit);
    return 0;
}
