#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
   dp[e][f] = minimum drops needed in the worst case with e eggs and f floors.

   If we drop an egg from floor x:
     - it breaks    -> solve e-1 eggs, x-1 lower floors
     - it survives  -> solve e eggs, f-x higher floors

   Therefore:
     dp[e][f] = 1 + min_x max(dp[e-1][x-1], dp[e][f-x])
*/

int main(void) {
    int E, F;

    printf("Enter number of eggs E and floors F: ");
    if (scanf("%d %d", &E, &F) != 2 || E < 1 || F < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int e = 0; e <= E; ++e) {
        dp[e] = (int *)malloc((F + 1) * sizeof(int));
        if (dp[e] == NULL) {
            printf("Memory allocation failed.\n");
            for (int i = 0; i < e; ++i) free(dp[i]);
            free(dp);
            return 1;
        }
    }

    /* Base cases. */
    for (int f = 0; f <= F; ++f) dp[1][f] = f;
    for (int e = 1; e <= E; ++e) dp[e][0] = 0;
    if (F >= 1) {
        for (int e = 1; e <= E; ++e) dp[e][1] = 1;
    }

    for (int e = 2; e <= E; ++e) {
        for (int f = 2; f <= F; ++f) {
            dp[e][f] = INT_MAX;
            for (int x = 1; x <= f; ++x) {
                int worst = dp[e - 1][x - 1] > dp[e][f - x]
                             ? dp[e - 1][x - 1]
                             : dp[e][f - x];
                int attempts = worst + 1;
                if (attempts < dp[e][f]) dp[e][f] = attempts;
            }
        }
    }

    printf("Minimum worst-case droppings = %d\n", dp[E][F]);

    /* Print a useful DP table for validation. */
    printf("\nDP table (rows = eggs, columns = floors):\n");
    for (int e = 1; e <= E; ++e) {
        for (int f = 0; f <= F; ++f) {
            printf("%4d", dp[e][f]);
        }
        printf("\n");
    }

    /* For the lab's original instance. */
    if (E == 2 && F == 100)
        printf("\nFor 2 eggs and 100 floors, answer = %d drops.\n", dp[E][F]);

    for (int e = 0; e <= E; ++e) free(dp[e]);
    free(dp);
    return 0;
}
