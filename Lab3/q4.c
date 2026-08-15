#include <stdio.h>
#define MAX 32

void add(int A[MAX][MAX], int B[MAX][MAX],
         int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];

    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];

    int P1[MAX][MAX], P2[MAX][MAX];
    int P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX];
    int P7[MAX][MAX];

    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Divide matrices
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // P1 = A11 * (B12 - B22)
    subtract(B12, B22, temp1, k);
    strassen(A11, temp1, P1, k);

    // P2 = (A11 + A12) * B22
    add(A11, A12, temp1, k);
    strassen(temp1, B22, P2, k);

    // P3 = (A21 + A22) * B11
    add(A21, A22, temp1, k);
    strassen(temp1, B11, P3, k);

    // P4 = A22 * (B21 - B11)
    subtract(B21, B11, temp1, k);
    strassen(A22, temp1, P4, k);

    // P5 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, k);
    add(B11, B22, temp2, k);
    strassen(temp1, temp2, P5, k);

    // P6 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, k);
    add(B21, B22, temp2, k);
    strassen(temp1, temp2, P6, k);

    // P7 = (A11 - A21) * (B11 + B12)
    subtract(A11, A21, temp1, k);
    add(B11, B12, temp2, k);
    strassen(temp1, temp2, P7, k);

    // C11 = P5 + P4 - P2 + P6
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                P5[i][j] + P4[i][j]
                - P2[i][j] + P6[i][j];

            C[i][j + k] =
                P1[i][j] + P2[i][j];

            C[i + k][j] =
                P3[i][j] + P4[i][j];

            C[i + k][j + k] =
                P5[i][j] + P1[i][j]
                - P3[i][j] - P7[i][j];
        }
    }
}

int main()
{
    int n;

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter Matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(A, B, C, n);

    printf("\nResult Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);

        printf("\n");
    }

    return 0;
}