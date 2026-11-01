#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define HASH_SIZE (1 << 18)

char words[MAXN][11];
int hashTable[HASH_SIZE];

int distA[MAXN], distB[MAXN];

int frontA[MAXN], frontB[MAXN];
int nextA[MAXN], nextB[MAXN];

int N, L, total;

// Hash function
unsigned int hashFunction(const char *s) {
    unsigned int h = 2166136261u;

    for (int i = 0; i < L; i++) {
        h ^= (unsigned char)s[i];
        h *= 16777619u;
    }

    return h & (HASH_SIZE - 1);
}

// Search for a word in the hash table
int findWord(const char *s) {
    unsigned int h = hashFunction(s);

    while (hashTable[h] != 0) {
        int id = hashTable[h] - 1;

        if (strcmp(words[id], s) == 0)
            return id;

        h = (h + 1) & (HASH_SIZE - 1);
    }

    return -1;
}

// Insert a word if it does not already exist
int insertWord(const char *s) {
    int id = findWord(s);

    if (id != -1)
        return id;

    strcpy(words[total], s);

    unsigned int h = hashFunction(s);

    while (hashTable[h] != 0)
        h = (h + 1) & (HASH_SIZE - 1);

    hashTable[h] = total + 1;

    return total++;
}

// Bidirectional BFS
int bidirectionalBFS(int start, int target) {

    if (start == target)
        return 0;

    int *f1 = frontA;
    int *f2 = frontB;
    int *n1 = nextA;
    int *n2 = nextB;

    int *d1 = distA;
    int *d2 = distB;

    int c1 = 1, c2 = 1;

    f1[0] = start;
    f2[0] = target;

    d1[start] = 0;
    d2[target] = 0;

    char temp[11];

    while (c1 > 0 && c2 > 0) {

        // Always expand the smaller frontier
        if (c1 > c2) {
            int *t;

            t = f1; f1 = f2; f2 = t;
            t = n1; n1 = n2; n2 = t;
            t = d1; d1 = d2; d2 = t;

            int x = c1;
            c1 = c2;
            c2 = x;
        }

        int nc = 0;

        // Expand current level
        for (int i = 0; i < c1; i++) {

            int u = f1[i];

            strcpy(temp, words[u]);

            // Change each character
            for (int j = 0; j < L; j++) {

                char original = temp[j];

                for (char ch = 'a'; ch <= 'z'; ch++) {

                    if (ch == original)
                        continue;

                    temp[j] = ch;

                    int v = findWord(temp);

                    if (v == -1)
                        continue;

                    // Check whether both searches have met
                    if (d2[v] != -1) {
                        return d1[u] + 1 + d2[v];
                    }

                    // Avoid revisiting words
                    if (d1[v] == -1) {
                        d1[v] = d1[u] + 1;
                        n1[nc++] = v;
                    }
                }

                temp[j] = original;
            }
        }

        // Move to the next BFS level
        int *t = f1;
        f1 = n1;
        n1 = t;

        c1 = nc;
    }

    return -1;
}

int main() {

    scanf("%d %d", &N, &L);

    total = 0;

    // Read dictionary
    for (int i = 0; i < N; i++) {
        char s[11];
        scanf("%10s", s);
        insertWord(s);
    }

    char A[11], B[11];

    scanf("%10s %10s", A, B);

    // Target must exist in dictionary
    int target = findWord(B);

    if (target == -1) {
        printf("-1\n");
        return 0;
    }

    // Starting word may or may not be in dictionary
    int start = insertWord(A);

    if (strcmp(A, B) == 0) {
        printf("0\n");
        return 0;
    }

    // Initialize distances
    for (int i = 0; i < total; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    int answer = bidirectionalBFS(start, target);

    printf("%d\n", answer);

    return 0;
}