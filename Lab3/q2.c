#include <stdio.h>

int findDefective(int coins[], int left, int right)
{
    if (left == right)
        return left;

    int n = right - left + 1;

    int mid = left + n / 2 - 1;

    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = left; i <= mid; i++)
        leftWeight += coins[i];

    for (int i = mid + 1; i <= right; i++)
        rightWeight += coins[i];

    // Left side is lighter
    if (leftWeight < rightWeight)
    {
        return findDefective(coins, left, mid);
    }

    // Right side is lighter
    else if (rightWeight < leftWeight)
    {
        return findDefective(coins, mid + 1, right);
    }

    // Both sides equal
    else
    {
        return -1;
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of coins:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    int index = findDefective(coins, 0, n - 1);

    if (index == -1)
        printf("No defective coin found.\n");
    else
        printf("Possible defective coin is at index %d with weight %d.\n",
               index, coins[index]);

    return 0;
}