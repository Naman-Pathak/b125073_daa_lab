#include <stdio.h>
#include <stdlib.h>

/*
   dp[n] = minimum toggles required to turn off n switches initially ON.

   For n >= 3 the optimal process has the recurrence:
       dp[n] = 2*dp[n-1] + (n % 2)
   with dp[1]=1, dp[2]=2.

   Equivalent closed form:
       dp[n] = floor(2^(n+1) / 3)
*/

int main(void) {
    int n;

    printf("Enter number of switches n (1..60): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 60) {
        printf("Invalid input.\n");
        return 1;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    dp[0] = 0;
    dp[1] = 1;
    if (n >= 2) dp[2] = 2;

    for (int i = 3; i <= n; ++i) {
        dp[i] = 2ULL * dp[i - 1] + (unsigned long long)(i % 2);
    }

    printf("Minimum number of moves = %llu\n", dp[n]);

    printf("\nDP values:\n");
    for (int i = 1; i <= n; ++i) {
        printf("n=%d -> %llu\n", i, dp[i]);
    }

    free(dp);
    return 0;
}
