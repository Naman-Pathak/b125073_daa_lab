
#include <stdio.h>

#define MAX 100

typedef struct {
    long long weight;
    int left;
    int right;
    int depth;
} Node;

Node tree[2 * MAX];
int nodeCount = 0;

int buildTree(long long w[], int n) {
    int roots[MAX];

    for (int i = 0; i < n; i++) {
        tree[nodeCount].weight = w[i];
        tree[nodeCount].left = -1;
        tree[nodeCount].right = -1;
        roots[i] = nodeCount++;
    }

    int count = n;

    while (count > 1) {
        int best = 0;
        long long minSum = tree[roots[0]].weight
                         + tree[roots[1]].weight;

        for (int i = 1; i < count - 1; i++) {
            long long sum = tree[roots[i]].weight
                          + tree[roots[i + 1]].weight;

            if (sum < minSum) {
                minSum = sum;
                best = i;
            }
        }

        int left = roots[best];
        int right = roots[best + 1];

        tree[nodeCount].weight = minSum;
        tree[nodeCount].left = left;
        tree[nodeCount].right = right;

        roots[best] = nodeCount++;

        for (int i = best + 1; i < count - 1; i++)
            roots[i] = roots[i + 1];

        count--;
    }

    return roots[0];
}

void calculateDepth(int root, int depth) {
    if (root == -1)
        return;

    tree[root].depth = depth;

    calculateDepth(tree[root].left, depth + 1);
    calculateDepth(tree[root].right, depth + 1);
}

int main(void) {
    int n;
    long long w[MAX];
    long long cost = 0;

    printf("Enter number of weights: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of weights.\n");
        return 1;
    }

    printf("Enter weights in required order:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] <= 0) {
            printf("Weights must be positive integers.\n");
            return 1;
        }
    }

    int root = buildTree(w, n);
    calculateDepth(root, 0);

    for (int i = 0; i < n; i++)
        cost += w[i] * tree[i].depth;

    printf("Weighted path cost = %lld\n", cost);

    return 0;
}
