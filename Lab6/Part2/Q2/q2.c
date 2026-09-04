#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-10

double **createMatrix(int n) {
    double **a = malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
        a[i] = malloc(n * sizeof(double));

    return a;
}

void freeMatrix(double **a, int n) {
    for (int i = 0; i < n; i++)
        free(a[i]);

    free(a);
}

void inputMatrix(double **a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);
}

void printMatrix(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.2f ", a[i][j]);

        printf("\n");
    }
}

void addMatrices(double **a, double **b, int n) {
    printf("A + B:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.2f ", a[i][j] + b[i][j]);

        printf("\n");
    }
}

void multiplyMatrices(double **a, double **b, int n) {
    double **c = createMatrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;

            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    printf("A x B:\n");
    printMatrix(c, n);

    freeMatrix(c, n);
}

int isZeroMatrix(double **a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fabs(a[i][j]) > EPS)
                return 0;

    return 1;
}

int isSymmetric(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[i][j] - a[j][i]) > EPS)
                return 0;
        }
    }

    return 1;
}

double determinant(double **a, int n) {
    double **temp = createMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = a[i][j];

    double det = 1.0;

    for (int i = 0; i < n; i++) {
        int pivot = i;

        for (int j = i + 1; j < n; j++) {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;
        }

        if (fabs(temp[pivot][i]) < EPS) {
            freeMatrix(temp, n);
            return 0;
        }

        if (pivot != i) {
            double *row = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = row;

            det *= -1;
        }

        det *= temp[i][i];

        for (int j = i + 1; j < n; j++) {
            double factor = temp[j][i] / temp[i][i];

            for (int k = i + 1; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    freeMatrix(temp, n);

    return det;
}

void transposeInPlace(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

void dominantEigenPair(double **a, int n) {
    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
        x[i] = 1.0;

    double eigenvalue = 0;

    int maxIterations = 1000;

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        for (int i = 0; i < n; i++) {
            y[i] = 0;

            for (int j = 0; j < n; j++)
                y[i] += a[i][j] * x[j];
        }

        double norm = 0;

        for (int i = 0; i < n; i++)
            norm += y[i] * y[i];

        norm = sqrt(norm);

        if (norm < EPS) {
            printf("Cannot determine a dominant eigenvector.\n");
            free(x);
            free(y);
            return;
        }

        for (int i = 0; i < n; i++)
            x[i] = y[i] / norm;
    }

    double numerator = 0;
    double denominator = 0;

    for (int i = 0; i < n; i++) {
        double value = 0;

        for (int j = 0; j < n; j++)
            value += a[i][j] * x[j];

        numerator += x[i] * value;
        denominator += x[i] * x[i];
    }

    eigenvalue = numerator / denominator;

    printf("Dominant eigenvalue = %.6f\n", eigenvalue);

    printf("Corresponding eigenvector:\n");

    for (int i = 0; i < n; i++)
        printf("%.6f ", x[i]);

    printf("\n");

    free(x);
    free(y);
}

int main() {
    int n;

    printf("Enter order of matrices: ");
    scanf("%d", &n);

    double **a = createMatrix(n);
    double **b = createMatrix(n);

    printf("Enter matrix A:\n");
    inputMatrix(a, n);

    printf("Enter matrix B:\n");
    inputMatrix(b, n);

    printf("\n");
    addMatrices(a, b, n);

    printf("\n");
    multiplyMatrices(a, b, n);

    printf("\n");

    if (isZeroMatrix(a, n))
        printf("Matrix A is a zero matrix.\n");
    else
        printf("Matrix A is not a zero matrix.\n");

    if (isSymmetric(a, n))
        printf("Matrix A is symmetric.\n");
    else
        printf("Matrix A is not symmetric.\n");

    printf("Determinant of A = %.6f\n", determinant(a, n));

    dominantEigenPair(a, n);

    transposeInPlace(a, n);

    printf("Transpose of A:\n");
    printMatrix(a, n);

    freeMatrix(a, n);
    freeMatrix(b, n);

    return 0;
}