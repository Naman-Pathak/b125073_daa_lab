#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef long long ll;

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

typedef struct Node {
    int state;
    struct Node *next;
} Node;

Node *front = NULL, *rear = NULL;

int isEmpty(void) {
    return front == NULL;
}

void enqueue(int state) {
    Node *temp = malloc(sizeof(Node));
    temp->state = state;
    temp->next = NULL;

    if (rear == NULL) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
}

int dequeue(void) {
    Node *temp = front;
    int state = temp->state;

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
    return state;
}

void addEdge(Edge **head, int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = head[u];
    head[u] = e;
}

int main(void) {
    int n, m, S;
    ll C;

    printf("Enter vertices, edges, source and penalty: ");
    if (scanf("%d %d %d %lld", &n, &m, &S, &C) != 4 ||
        n <= 0 || m < 0 || S < 0 || S >= n || C < 0) {
        printf("Invalid input\n");
        return 1;
    }

    Edge **head = calloc(n, sizeof(Edge *));
    if (head == NULL)
        return 1;

    printf("Enter each directed edge (u v weight):\n");

    for (int i = 0; i < m; i++) {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 0 || u >= n || v < 0 || v >= n ||
            (w != 0 && w != 1)) {
            printf("Invalid edge input\n");
            return 1;
        }

        addEdge(head, u, v, w);
    }

    // State 2*v represents even parity.
    // State 2*v+1 represents odd parity.
    ll (*dist)[2] = malloc(n * sizeof(*dist));
    if (dist == NULL)
        return 1;

    for (int v = 0; v < n; v++) {
        dist[v][0] = INF;
        dist[v][1] = INF;
    }

    dist[S][0] = 0;
    enqueue(2 * S);

    while (!isEmpty()) {
        int state = dequeue();
        int u = state / 2;
        int parity = state % 2;

        for (Edge *e = head[u]; e != NULL; e = e->next) {
            int v = e->to;
            int w = e->weight;
            int newParity = parity ^ w;

            ll newDist = dist[u][parity] + w;

            if (newDist < dist[v][newParity]) {
                dist[v][newParity] = newDist;
                enqueue(2 * v + newParity);
            }
        }
    }

    printf("\nMinimum effective costs:\n");

    for (int v = 0; v < n; v++) {
        if (dist[v][0] == INF && dist[v][1] == INF) {
            printf("Vertex %d: Unreachable\n", v);
            continue;
        }

        ll ans = dist[v][0];

        if (dist[v][1] != INF &&
            dist[v][1] + C < ans) {
            ans = dist[v][1] + C;
        }

        printf("Vertex %d: %lld\n", v, ans);
    }

    // Free memory
    while (!isEmpty())
        dequeue();

    for (int v = 0; v < n; v++) {
        Edge *e = head[v];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(head);
    free(dist);

    return 0;
}
