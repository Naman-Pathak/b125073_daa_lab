#include <stdio.h>
#include <stdlib.h>

int *parent, *size;
int R, C;

// Find the representative of a component
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

// Merge two components
int unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);

    if (rx == ry)
        return 0;

    // Union by size
    if (size[rx] < size[ry]) {
        int temp = rx;
        rx = ry;
        ry = temp;
    }

    parent[ry] = rx;
    size[rx] += size[ry];

    return 1;
}

// Convert 2D coordinates to a 1D index
int indexOf(int r, int c) {
    return r * C + c;
}

int main(void) {
    int k;

    printf("Enter rows, columns and operations: ");
    if (scanf("%d %d %d", &R, &C, &k) != 3 ||
        R <= 0 || C <= 0 || k < 0 ||
        (long long)R * C > 2147483647LL) {
        printf("Invalid input.\n");
        return 1;
    }

    int total = R * C;

    parent = malloc((size_t)total * sizeof(int));
    size = calloc((size_t)total, sizeof(int));

    if (parent == NULL || size == NULL) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(size);
        return 1;
    }

    // -1 indicates that the cell is water
    for (int i = 0; i < total; i++)
        parent[i] = -1;

    int islands = 0;

    // Four directions: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter each land position (row column):\n");

    for (int i = 0; i < k; i++) {
        int r, c;

        if (scanf("%d %d", &r, &c) != 2) {
            printf("Invalid operation input.\n");
            free(parent);
            free(size);
            return 1;
        }

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid position. Island count: %d\n",
                   islands);
            continue;
        }

        int id = indexOf(r, c);

        // Duplicate land operation
        if (parent[id] != -1) {
            printf("%d ", islands);
            continue;
        }

        // Convert water into land
        parent[id] = id;
        size[id] = 1;
        islands++;

        // Merge with neighboring land cells
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;

            int nid = indexOf(nr, nc);

            if (parent[nid] != -1) {
                if (unite(id, nid))
                    islands--;
            }
        }

        printf("%d ", islands);
    }

    printf("\n");

    free(parent);
    free(size);

    return 0;
}
