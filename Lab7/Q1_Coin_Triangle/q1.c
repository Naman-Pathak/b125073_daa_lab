#include <stdio.h>
#include <stdlib.h>

/*
   Q1: Invert the coin triangle.
   For n rows, the total number of coins is T(n) = n(n+1)/2.
   The minimum number of moves is floor(T(n) / 3).

   We compute T(n) using a small DP/prefix-sum table:
       dp[i] = dp[i-1] + i
   so dp[n] = T(n).
*/

int main(void) {
    int n;

    printf("Enter number of rows n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. n must be >= 1.\n");
        return 1;
    }

    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + i;
    }

    long long total_coins = dp[n];
    long long min_moves = total_coins / 3;

    printf("Total coins = %lld\n", total_coins);
    printf("Minimum moves = %lld\n", min_moves);

    free(dp);
    return 0;
}
