#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

void fft(double complex a[], int n, int invert) {
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;

        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if (i < j) {
            double complex temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2.0 * PI / len;

        if (!invert)
            angle = -angle;

        double complex wlen = cos(angle) + I * sin(angle);

        for (int i = 0; i < n; i += len) {
            double complex w = 1;

            for (int j = 0; j < len / 2; j++) {
                double complex u = a[i + j];
                double complex v = a[i + j + len / 2] * w;

                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;

                w *= wlen;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}

int main() {
    int m, n;

    printf("Enter length of vector A: ");
    scanf("%d", &m);

    printf("Enter length of vector B: ");
    scanf("%d", &n);

    if (n < m) {
        printf("Condition n >= m is not satisfied.\n");
        return 0;
    }

    int resultSize = m + n - 1;

    int size = 1;

    while (size < resultSize)
        size <<= 1;

    double complex *A = calloc(size, sizeof(double complex));
    double complex *B = calloc(size, sizeof(double complex));

    printf("Enter %d elements of A:\n", m);

    for (int i = 0; i < m; i++) {
        double value;
        scanf("%lf", &value);
        A[i] = value;
    }

    printf("Enter %d elements of B:\n", n);

    for (int i = 0; i < n; i++) {
        double value;
        scanf("%lf", &value);
        B[i] = value;
    }

    fft(A, size, 0);
    fft(B, size, 0);

    for (int i = 0; i < size; i++)
        A[i] *= B[i];

    fft(A, size, 1);

    printf("Convolution vector C:\n");

    for (int i = 0; i < resultSize; i++) {
        double value = creal(A[i]);

        if (fabs(value) < 1e-9)
            value = 0;

        printf("%.6f ", value);
    }

    printf("\n");

    free(A);
    free(B);

    return 0;
}