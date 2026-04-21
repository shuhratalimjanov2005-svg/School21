#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double determinant(double **matrix, int n);
void get_minor(double **matrix, double **minor, int row, int col, int n);

int main() {
    int rows, cols;
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows != cols) {
        printf("n/a");
        return 0;
    }

    
    double **matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                printf("n/a");
                for (int k = 0; k <= i; k++) free(matrix[k]);
                free(matrix);
                return 0;
            }
        }
    }

    printf("%.6f", determinant(matrix, rows));

    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
    return 0;
}

void get_minor(double **matrix, double **minor, int row, int col, int n) {
    int i_minor = 0, j_minor = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        j_minor = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            minor[i_minor][j_minor] = matrix[i][j];
            j_minor++;
        }
        i_minor++;
    }
}

double determinant(double **matrix, int n) {
    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    double **minor = malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++) minor[i] = malloc((n - 1) * sizeof(double));

    int sign = 1;
    for (int j = 0; j < n; j++) {
        get_minor(matrix, minor, 0, j, n);
        det += sign * matrix[0][j] * determinant(minor, n - 1);
        sign = -sign;
    }

    for (int i = 0; i < n - 1; i++) free(minor[i]);
    free(minor);
    return det;
}
