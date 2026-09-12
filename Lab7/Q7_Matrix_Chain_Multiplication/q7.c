#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
   Matrix Chain Multiplication.

   There are n matrices:
       A1: p0 x p1, A2: p1 x p2, ..., An: p(n-1) x pn

   dp[i][j] = minimum scalar multiplications needed for Ai...Aj.
   split[i][j] = k giving the optimal final split.

   Recurrence:
       dp[i][j] = min_{i <= k < j}
                  dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]
*/

void print_optimal_parenthesization(int **split, int i, int j) {
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");
    print_optimal_parenthesization(split, i, split[i][j]);
    printf(" x ");
    print_optimal_parenthesization(split, split[i][j] + 1, j);
    printf(")");
}

int main(void) {
    int n;

    printf("Enter number of matrices n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input.\n");
        return 1;
    }

    long long *p = (long long *)malloc((n + 1) * sizeof(long long));
    if (!p) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d+1 dimensions p0 p1 ... p%d: ", n, n);
    for (int i = 0; i <= n; ++i) {
        if (scanf("%lld", &p[i]) != 1 || p[i] <= 0) {
            printf("Invalid dimensions.\n");
            free(p);
            return 1;
        }
    }

    long long **dp = (long long **)malloc((n + 1) * sizeof(long long *));
    int **split = (int **)malloc((n + 1) * sizeof(int *));
    if (!dp || !split) {
        printf("Memory allocation failed.\n");
        free(p);
        free(dp);
        free(split);
        return 1;
    }

    for (int i = 0; i <= n; ++i) {
        dp[i] = (long long *)malloc((n + 1) * sizeof(long long));
        split[i] = (int *)malloc((n + 1) * sizeof(int));
        if (!dp[i] || !split[i]) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j <= i; ++j) {
                free(dp[j]);
                free(split[j]);
            }
            free(dp);
            free(split);
            free(p);
            return 1;
        }
    }

    for (int i = 1; i <= n; ++i) dp[i][i] = 0;

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; ++k) {
                long long cost = dp[i][k] + dp[k + 1][j]
                               + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("Minimum scalar multiplications = %lld\n", dp[1][n]);
    printf("Optimal parenthesization = ");
    print_optimal_parenthesization(split, 1, n);
    printf("\n");

    printf("\nCost DP table:\n");
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j < i) printf("    -    ");
            else printf("%9lld ", dp[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i <= n; ++i) {
        free(dp[i]);
        free(split[i]);
    }
    free(dp);
    free(split);
    free(p);
    return 0;
}
