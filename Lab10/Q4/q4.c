
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int *parent, *size;
ll *sum;
int *head, *to, *nextEdge;
int *order, *active;
ll *answerBefore;
int edgeCount = 0;

// Find representative with path compression
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

// Add an undirected edge to the adjacency list
void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;

    to[edgeCount] = u;
    nextEdge[edgeCount] = head[v];
    head[v] = edgeCount++;
}

// Find maximum component sum among active vertices
ll getMax(int V, int *hasComponent) {
    ll best = LLONG_MIN;
    *hasComponent = 0;

    for (int i = 1; i <= V; i++) {
        if (active[i] && find(i) == i) {
            if (!*hasComponent || sum[i] > best)
                best = sum[i];

            *hasComponent = 1;
        }
    }

    return best;
}

int main(void) {
    int V, E;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2 ||
        V <= 0 || E < 0 || E > (INT_MAX / 2)) {
        printf("Invalid input.\n");
        return 1;
    }

    parent = malloc((size_t)(V + 1) * sizeof(int));
    size = malloc((size_t)(V + 1) * sizeof(int));
    sum = malloc((size_t)(V + 1) * sizeof(ll));
    head = malloc((size_t)(V + 1) * sizeof(int));
    active = calloc((size_t)(V + 1), sizeof(int));
    order = malloc((size_t)V * sizeof(int));
    answerBefore = malloc((size_t)V * sizeof(ll));
    to = malloc((size_t)(2 * E) * sizeof(int));
    nextEdge = malloc((size_t)(2 * E) * sizeof(int));

    if (!parent || !size || !sum || !head || !active ||
        !order || !answerBefore || !to || !nextEdge) {
        printf("Memory allocation failed.\n");
        free(parent); free(size); free(sum); free(head);
        free(active); free(order); free(answerBefore);
        free(to); free(nextEdge);
        return 1;
    }

    ll *weight = malloc((size_t)(V + 1) * sizeof(ll));
    if (!weight) {
        printf("Memory allocation failed.\n");
        free(parent); free(size); free(sum); free(head);
        free(active); free(order); free(answerBefore);
        free(to); free(nextEdge);
        return 1;
    }

    printf("Enter vertex weights:\n");
    for (int i = 1; i <= V; i++) {
        if (scanf("%lld", &weight[i]) != 1) {
            printf("Invalid weight input.\n");
            free(parent); free(size); free(sum); free(head);
            free(active); free(order); free(answerBefore);
            free(to); free(nextEdge); free(weight);
            return 1;
        }
    }

    for (int i = 1; i <= V; i++)
        head[i] = -1;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge input.\n");
            free(parent); free(size); free(sum); free(head);
            free(active); free(order); free(answerBefore);
            free(to); free(nextEdge); free(weight);
            return 1;
        }
        addEdge(u, v);
    }

    printf("Enter deletion order (permutation of vertices):\n");
    int *seen = calloc((size_t)(V + 1), sizeof(int));
    if (!seen) {
        printf("Memory allocation failed.\n");
        free(parent); free(size); free(sum); free(head);
        free(active); free(order); free(answerBefore);
        free(to); free(nextEdge); free(weight);
        return 1;
    }

    for (int i = 0; i < V; i++) {
        if (scanf("%d", &order[i]) != 1 ||
            order[i] < 1 || order[i] > V ||
            seen[order[i]]) {
            printf("Invalid deletion order.\n");
            free(parent); free(size); free(sum); free(head);
            free(active); free(order); free(answerBefore);
            free(to); free(nextEdge); free(weight); free(seen);
            return 1;
        }
        seen[order[i]] = 1;
    }
    free(seen);

    // Initially all vertices are inactive.
    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        size[i] = 1;
        sum[i] = weight[i];
    }

    // Process deletions in reverse as vertex additions.
    for (int i = V - 1; i >= 0; i--) {
        int u = order[i];
        active[u] = 1;

        for (int e = head[u]; e != -1; e = nextEdge[e]) {
            int v = to[e];
            if (active[v])
                unite(u, v);
        }

        int hasComponent;
        answerBefore[i] = getMax(V, &hasComponent);
    }

    // After deleting order[i], the state equals the state
    // just before deleting order[i + 1].
    printf("Maximum component sum after each deletion:\n");

    for (int i = 0; i < V; i++) {
        if (i == V - 1) {
            printf("After deleting %d: No components\n", order[i]);
        } else {
            printf("After deleting %d: %lld\n",
                   order[i], answerBefore[i + 1]);
        }
    }

    free(parent); free(size); free(sum); free(head);
    free(active); free(order); free(answerBefore);
    free(to); free(nextEdge); free(weight);

    return 0;
}
