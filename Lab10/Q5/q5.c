#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int root;
    int index;
    int value;
} Item;

int *parent, *size;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (size[u] < size[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    parent[v] = u;
    size[u] += size[v];
}

int compareIndex(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->index > y->index) - (x->index < y->index);
}

int compareValue(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->value > y->value) - (x->value < y->value);
}

int main(void) {
    int n, m;

    scanf("%d %d", &n, &m);

    int *A = malloc(n * sizeof(int));
    int *ans = malloc(n * sizeof(int));
    parent = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));

    Item *positions = malloc(n * sizeof(Item));
    Item *values = malloc(n * sizeof(Item));

    if (!A || !ans || !parent || !size ||
        !positions || !values) {
        fprintf(stderr, "Memory allocation failed\n");
        free(A);
        free(ans);
        free(parent);
        free(size);
        free(positions);
        free(values);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // Convert 1-based positions to 0-based indices.
        unite(u - 1, v - 1);
    }

    for (int i = 0; i < n; i++) {
        int r = find(i);

        positions[i].root = r;
        positions[i].index = i;

        values[i].root = r;
        values[i].value = A[i];
    }

    // Group positions by component and sort indices.
    qsort(positions, n, sizeof(Item), compareIndex);

    // Group values by component and sort values.
    qsort(values, n, sizeof(Item), compareValue);

    // Match sorted values with sorted positions
    // within each connected component.
    for (int i = 0; i < n; i++) {
        ans[positions[i].index] = values[i].value;
    }

    printf("Lexicographically smallest permutation:\n");

    for (int i = 0; i < n; i++) {
        printf("%d", ans[i]);
        if (i < n - 1)
            printf(" ");
    }
    printf("\n");

    free(A);
    free(ans);
    free(parent);
    free(size);
    free(positions);
    free(values);

    return 0;
}
