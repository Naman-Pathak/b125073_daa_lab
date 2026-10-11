#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of children: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *rating = malloc((size_t)n * sizeof(int));
    int *candy = malloc((size_t)n * sizeof(int));

    if (rating == NULL || candy == NULL) {
        printf("Memory allocation failed.\n");
        free(rating);
        free(candy);
        return 1;
    }

    printf("Enter ratings of children:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            printf("Invalid rating.\n");
            free(rating);
            free(candy);
            return 1;
        }

        candy[i] = 1;
    }

    // First pass: Left to right
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    // Second pass: Right to left
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1]) {
            if (candy[i] < candy[i + 1] + 1) {
                candy[i] = candy[i + 1] + 1;
            }
        }
    }

    long long total = 0;

    for (int i = 0; i < n; i++) {
        total += candy[i];
    }

    printf("Candies given to each child: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", candy[i]);
    }

    printf("\nMinimum total candies = %lld\n", total);

    free(rating);
    free(candy);

    return 0;
}
