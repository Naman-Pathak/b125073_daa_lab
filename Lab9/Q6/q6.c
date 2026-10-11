
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100000
#define ALPHABET 256

typedef struct {
    unsigned char ch;
    int freq;
} Node;

typedef struct {
    Node node;
    int releaseAt;
} WaitingNode;

Node heap[ALPHABET];
WaitingNode waiting[ALPHABET];

int heapSize = 0;
int front = 0, rear = 0, waitSize = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node x) {
    int i = heapSize++;
    heap[i] = x;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].freq >= heap[i].freq)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

Node pop(void) {
    Node result = heap[0];
    heapSize--;

    if (heapSize > 0) {
        heap[0] = heap[heapSize];
        int i = 0;

        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < heapSize &&
                heap[left].freq > heap[largest].freq)
                largest = left;

            if (right < heapSize &&
                heap[right].freq > heap[largest].freq)
                largest = right;

            if (largest == i)
                break;

            swap(&heap[i], &heap[largest]);
            i = largest;
        }
    }

    return result;
}

void enqueue(Node x, int releaseAt) {
    waiting[rear] = (WaitingNode){x, releaseAt};
    rear = (rear + 1) % ALPHABET;
    waitSize++;
}

WaitingNode dequeue(void) {
    WaitingNode x = waiting[front];
    front = (front + 1) % ALPHABET;
    waitSize--;
    return x;
}

int main(void) {
    char s[MAX_LEN + 1];
    int k, freq[ALPHABET] = {0};

    printf("Enter string: ");
    if (scanf("%100000s", s) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid K.\n");
        return 1;
    }

    int n = (int)strlen(s);

    if (k <= 1) {
        printf("Reorganised string: %s\n", s);
        return 0;
    }

    for (int i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    // Build the max-heap
    for (int i = 0; i < ALPHABET; i++) {
        if (freq[i] > 0) {
            Node x = {(unsigned char)i, freq[i]};
            push(x);
        }
    }

    char result[MAX_LEN + 1];
    int pos = 0;

    for (int i = 0; i < n; i++) {
        // Release characters whose cooldown has ended
        while (waitSize > 0 &&
               waiting[front].releaseAt <= i) {
            WaitingNode w = dequeue();
            push(w.node);
        }

        // No character is available
        if (heapSize == 0) {
            printf("Reorganised string: \n");
            return 0;
        }

        Node current = pop();
        result[pos++] = (char)current.ch;
        current.freq--;

        // Prevent reuse until K positions have passed
        if (current.freq > 0)
            enqueue(current, i + k);
    }

    result[pos] = '\0';

    printf("Reorganised string: %s\n", result);
    return 0;
}
