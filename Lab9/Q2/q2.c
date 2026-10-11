#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

typedef struct Node {
    char symbol;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *heap[MAX_SYMBOLS * 2];
    int size;
} MinHeap;

typedef struct {
    char symbol;
    int frequency;
    int length;
    unsigned int code;
} Symbol;

/* ---------------- Min Heap Functions ---------------- */

void swap(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(MinHeap *h, Node *node) {

    int i = h->size;
    h->heap[h->size++] = node;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (h->heap[parent]->frequency <=
            h->heap[i]->frequency)
            break;

        swap(&h->heap[parent], &h->heap[i]);

        i = parent;
    }
}

Node *extractMin(MinHeap *h) {

    Node *result = h->heap[0];

    h->heap[0] = h->heap[--h->size];

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < h->size &&
            h->heap[left]->frequency <
            h->heap[smallest]->frequency) {

            smallest = left;
        }

        if (right < h->size &&
            h->heap[right]->frequency <
            h->heap[smallest]->frequency) {

            smallest = right;
        }

        if (smallest == i)
            break;

        swap(&h->heap[i], &h->heap[smallest]);

        i = smallest;
    }

    return result;
}

/* ---------------- Create Node ---------------- */

Node *createNode(char symbol, int frequency) {

    Node *node = (Node *)malloc(sizeof(Node));

    node->symbol = symbol;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* ---------------- Build Huffman Tree ---------------- */

Node *buildHuffmanTree(Symbol symbols[], int n) {

    MinHeap heap;
    heap.size = 0;

    for (int i = 0; i < n; i++) {

        Node *node =
            createNode(symbols[i].symbol,
                       symbols[i].frequency);

        insertHeap(&heap, node);
    }

    while (heap.size > 1) {

        Node *left = extractMin(&heap);
        Node *right = extractMin(&heap);

        Node *parent =
            createNode('\0',
                       left->frequency +
                       right->frequency);

        parent->left = left;
        parent->right = right;

        insertHeap(&heap, parent);
    }

    return extractMin(&heap);
}

/* ---------------- Find Code Lengths ---------------- */

void findLengths(Node *root, int depth,
                 Symbol symbols[], int n) {

    if (root == NULL)
        return;

    /* Leaf node */
    if (root->left == NULL &&
        root->right == NULL) {

        for (int i = 0; i < n; i++) {

            if (symbols[i].symbol == root->symbol) {
                symbols[i].length = depth;
                break;
            }
        }

        return;
    }

    findLengths(root->left, depth + 1,
                 symbols, n);

    findLengths(root->right, depth + 1,
                 symbols, n);
}

/* ---------------- Sort for Canonical Codes ---------------- */

int compareSymbols(const void *a, const void *b) {

    Symbol *x = (Symbol *)a;
    Symbol *y = (Symbol *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return x->symbol - y->symbol;
}

/* ---------------- Generate Canonical Codes ---------------- */

void generateCanonicalCodes(Symbol symbols[], int n) {

    qsort(symbols, n, sizeof(Symbol),
          compareSymbols);

    unsigned int code = 0;

    symbols[0].code = code;

    for (int i = 1; i < n; i++) {

        code++;

        int shift =
            symbols[i].length -
            symbols[i - 1].length;

        code <<= shift;

        symbols[i].code = code;
    }
}

/* ---------------- Print Binary Code ---------------- */

void printBinary(unsigned int code, int length) {

    for (int i = length - 1; i >= 0; i--) {

        if (code & (1U << i))
            printf("1");
        else
            printf("0");
    }
}

/* ---------------- Free Tree ---------------- */

void freeTree(Node *root) {

    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

/* ---------------- Main ---------------- */

int main() {

    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    Symbol symbols[MAX_SYMBOLS];

    printf("\nEnter symbol and frequency:\n");

    for (int i = 0; i < n; i++) {

        scanf(" %c %d",
              &symbols[i].symbol,
              &symbols[i].frequency);

        symbols[i].length = 0;
        symbols[i].code = 0;
    }

    /* Build Huffman tree */
    Node *root =
        buildHuffmanTree(symbols, n);

    /* Find code lengths */
    findLengths(root, 0, symbols, n);

    /* Generate canonical codes */
    generateCanonicalCodes(symbols, n);

    printf("\nCanonical Huffman Codebook\n");
    printf("--------------------------\n");

    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < n; i++) {

        printf("%c\t%d\t\t%d\t",
               symbols[i].symbol,
               symbols[i].frequency,
               symbols[i].length);

        printBinary(symbols[i].code,
                    symbols[i].length);

        printf("\n");
    }

    freeTree(root);

    return 0;
}