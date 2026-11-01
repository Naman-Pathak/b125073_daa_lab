
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

void addEdge(Edge **graph, int u, int v) {
    Edge *e1 = malloc(sizeof(Edge));
    e1->to = v;
    e1->next = graph[u];
    graph[u] = e1;

    Edge *e2 = malloc(sizeof(Edge));
    e2->to = u;
    e2->next = graph[v];
    graph[v] = e2;
}

int main(void) {
    int n, m, K, R;

    printf("Enter number of vertices, edges, hubs and radius: ");
    if (scanf("%d %d %d %d", &n, &m, &K, &R) != 4 ||
        n <= 0 || m < 0 || K <= 0 || K > n || R < 0) {
        printf("Invalid input\n");
        return 1;
    }

    Edge **graph = calloc(n + 1, sizeof(Edge *));
    int *owner = malloc((n + 1) * sizeof(int));
    int *dist = malloc((n + 1) * sizeof(int));
    int *queue = malloc((n + 1) * sizeof(int));

    if (!graph || !owner || !dist || !queue) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the undirected edges (u v):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > n || v < 1 || v > n) {
            printf("Invalid edge\n");
            return 1;
        }
        addEdge(graph, u, v);
    }

    for (int v = 1; v <= n; v++) {
        owner[v] = -1;
        dist[v] = -1;
    }

    int front = 0, rear = 0;

    printf("Enter the hub vertices in index order:\n");

    for (int i = 1; i <= K; i++) {
        int h;
        if (scanf("%d", &h) != 1 || h < 1 || h > n) {
            printf("Invalid hub\n");
            return 1;
        }

        // Hubs are indexed from 1 to K.
        // If a vertex is listed as multiple hubs,
        // retain the smallest hub index.
        if (owner[h] == -1 || i < owner[h]) {
            owner[h] = i;
            dist[h] = 0;
        }
    }

    // Enqueue all distinct hub vertices in increasing
    // hub-index order, avoiding duplicate vertices.
    for (int i = 1; i <= K; i++) {
        // Read hub list is needed for this pass, so instead
        // use the initial owner/dist values below.
    }

    // The vertices with distance zero are the hubs.
    // Queue them in vertex order; tie-breaking is handled
    // explicitly during equal-distance updates.
    for (int v = 1; v <= n; v++) {
        if (dist[v] == 0)
            queue[rear++] = v;
    }

    while (front < rear) {
        int u = queue[front++];

        if (dist[u] == R)
            continue;

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            int newDist = dist[u] + 1;

            if (dist[v] == -1) {
                dist[v] = newDist;
                owner[v] = owner[u];
                queue[rear++] = v;
            } else if (newDist < dist[v]) {
                dist[v] = newDist;
                owner[v] = owner[u];
                queue[rear++] = v;
            } else if (newDist == dist[v] &&
                       owner[u] < owner[v]) {
                owner[v] = owner[u];
            }
        }
    }

    printf("\nVertex\tOwner\tDistance\n");
    for (int v = 1; v <= n; v++) {
        if (dist[v] == -1 || dist[v] > R)
            printf("%d\t-1\t-1\n", v);
        else
            printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
    }

    for (int v = 1; v <= n; v++) {
        Edge *e = graph[v];
        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    free(owner);
    free(dist);
    free(queue);

    return 0;
}
