#include <stdio.h>
int max(int a, int b){
    return (a > b) ? a : b;
}
int main()
{
    int n, W;
    int i, w;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int weight[n + 1];
    int profit[n + 1];

    printf("Enter weights:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &weight[i]);

    printf("Enter profits:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &profit[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int dp[n + 1][W + 1];

    /*
       dp[i][w] = maximum profit obtained using
                  first i items with capacity w
    */

    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weight[i] <= w)
            {
                dp[i][w] = max(
                    profit[i] + dp[i - 1][w - weight[i]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("Maximum profit = %d\n", dp[n][W]);

    return 0;
}