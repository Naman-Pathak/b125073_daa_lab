
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *parent, *size;
long long *sum;

// Find component representative with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

// Merge two components
void unite(int u, int v) {
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return;

    // Union by size
    if (size[ru] < size[rv]) {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;
    size[ru] += size[rv];
    sum[ru] += sum[rv];
}

// Find maximum component weight with size <= K
long long getMaxWeight(int V, int K) {
    long long ans = LLONG_MIN;

    for (int i = 1; i <= V; i++) {
        if (parent[i] == i && size[i] <= K) {
            if (sum[i] > ans)
                ans = sum[i];
        }
    }

    return ans;
}

int main(void) {
    int V, E, K;

    printf("Enter vertices, edges and K: ");
    if (scanf("%d %d %d", &V, &E, &K) != 3 ||
        V <= 0 || E < 0 || K < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    parent = malloc((size_t)(V + 1) * sizeof(int));
    size = malloc((size_t)(V + 1) * sizeof(int));
    sum = malloc((size_t)(V + 1) * sizeof(long long));

    if (!parent || !size || !sum) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(size);
        free(sum);
        return 1;
    }

    // Read vertex weights and initialize components
    printf("Enter vertex weights:\n");
    for (int i = 1; i <= V; i++) {
        if (scanf("%lld", &sum[i]) != 1) {
            printf("Invalid weight input.\n");
            free(parent);
            free(size);
            free(sum);
            return 1;
        }

        parent[i] = i;
        size[i] = 1;
    }

    printf("Enter edges (u v):\n");

    for (int i = 1; i <= E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge input.\n");
            free(parent);
            free(size);
            free(sum);
            return 1;
        }

        unite(u, v);

        if (K == 0) {
            printf("After edge %d: No eligible component\n", i);
        } else {
            long long ans = getMaxWeight(V, K);
            printf("After edge %d: %lld\n", i, ans);
        }
    }

    free(parent);
    free(size);
    free(sum);

    return 0;
}
