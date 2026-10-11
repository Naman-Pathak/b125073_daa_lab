#include <stdio.h>

struct Item {
    double value;
    double weight;
    double decay;
    double density;
};

int main() {
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter capacity: ");
    scanf("%lf", &W);

    struct Item a[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate of item %d: ",
               i + 1);

        scanf("%lf %lf %lf",
              &a[i].value,
              &a[i].weight,
              &a[i].decay);

        // Initial density
        a[i].density = a[i].value / a[i].weight;
    }

    // Sort by density in decreasing order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (a[i].density < a[j].density) {
                struct Item temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    double totalValue = 0;
    double remaining = W;

    printf("\nSelected items:\n");

    for (int i = 0; i < n && remaining > 0; i++) {

        // Effective density at time i
        double effectiveDensity =
            a[i].density - a[i].decay * i;

        if (effectiveDensity <= 0)
            continue;

        if (a[i].weight <= remaining) {

            // Take complete item
            totalValue +=
                a[i].weight * effectiveDensity;

            remaining -= a[i].weight;

            printf("Item %d -> 100%%\n", i + 1);
        }
        else {

            // Take fraction of item
            double fraction =
                remaining / a[i].weight;

            totalValue +=
                remaining * effectiveDensity;

            printf("Item %d -> %.2f%%\n",
                   i + 1, fraction * 100);

            remaining = 0;
        }
    }

    printf("\nMaximum value = %.2lf\n", totalValue);
    printf("Remaining capacity = %.2lf\n", remaining);

    return 0;
}