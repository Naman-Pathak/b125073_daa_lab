#include <stdio.h>
#define MAX 100005
int parent[MAX];
int size[MAX];
int parity[MAX];
// Find representative and calculate parity relative to root
int find(int x) {
    if (parent[x] != x) {
        int p = parent[x];
        parent[x] = find(p);
        parity[x] ^= parity[p];
    }
    return parent[x];
}

// Insert edge (u, v) if it preserves bipartiteness
int addEdge(int u, int v) {
    int ru = find(u);
    int rv = find(v);

    int pu = parity[u];
    int pv = parity[v];

    // Both vertices are in the same component
    if (ru == rv) {
        // They must have opposite colors
        if ((pu ^ pv) == 1)
            return 1;  // Accept edge

        return 0;      // Reject edge
    }

    // Merge smaller component into larger component
    int linkParity = pu ^ pv ^ 1;

    if (size[ru] < size[rv]) {
        parent[ru] = rv;
        parity[ru] = linkParity;
        size[rv] += size[ru];
    } else {
        parent[rv] = ru;
        parity[rv] = linkParity;
        size[ru] += size[rv];
    }

    return 1;  // Accept edge
}

int main() {
    int V, E, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V < 1 || V >= MAX || E < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Initialize DSU
    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        size[i] = 1;
        parity[i] = 0;
    }

    printf("Enter edges one by one (u v):\n");

    for (int i = 1; i <= E; i++) {
        scanf("%d %d", &u, &v);

        if (u < 1 || u > V || v < 1 || v > V) {
            printf("Edge %d: Invalid vertices. Skipped.\n", i);
            continue;
        }

        if (addEdge(u, v)) {
            printf("Edge (%d, %d): Accepted\n", u, v);
        } else {
            printf("Edge (%d, %d): Rejected "
                   "- violates bipartiteness\n", u, v);
        }
    }
    printf("Final graph is bipartite.\n");
    return 0;
}
