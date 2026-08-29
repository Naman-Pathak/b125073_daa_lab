#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && a[left] > a[largest])
        largest = left;
    if(right < n && a[right] > a[largest])
        largest = right;
    if(largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}
void heapSort(int a[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for(int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    FILE *fp = fopen("heapinput.txt", "w");
    srand(time(NULL));
    for(int i = 0; i < n; i++) fprintf(fp, "%d ", rand() % 1000);
    fclose(fp);
    int a[n];
    fp = fopen("heapinput.txt", "r");
    for(int i = 0; i < n; i++) fscanf(fp, "%d", &a[i]);
    fclose(fp);
    heapSort(a, n);
    fp = fopen("heapoutput.txt", "w");
    for(int i = 0; i < n; i++) fprintf(fp, "%d ", a[i]);
    fclose(fp);
    printf("Heap Sort completed. Output stored in heapoutput.txt\n");
    return 0;
}
