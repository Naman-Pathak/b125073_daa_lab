#include <stdio.h>
typedef struct {
    int number;
    char colour;
} Item;
int main() {
    int n;
    printf("Enter number of items: ");
    scanf("%d", &n);
    Item a[n];
    printf("Enter number and colour (R/B/Y):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &a[i].number, &a[i].colour);
    }
    printf("\nSorted by colour:\n");
    // First: Red
    for (int i = 0; i < n; i++) {
        if (a[i].colour == 'R') {
            printf("(%d, R) ", a[i].number);
        }
    }

    // Second: Blue
    for (int i = 0; i < n; i++) {
        if (a[i].colour == 'B') {
            printf("(%d, B) ", a[i].number);
        }
    }

    // Third: Yellow
    for (int i = 0; i < n; i++) {
        if (a[i].colour == 'Y') {
            printf("(%d, Y) ", a[i].number);
        }
    }

    return 0;
}