#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double determinant(double **matrix, int n);
void get_minor(double **matrix, double **minor, int row, int col, int n);
void invert(double **matrix, int n);

int main() {
    int rows, cols;
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows != cols) {
        printf("n/a"); return 0;
    }

    double **matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                printf("n/a");
                for (int k = 0; k <= i; k++) free(matrix[k]);
                free(matrix); return 0;
            }
        }
    }

    double det = determinant(matrix, rows);
    if (fabs(det) < 1e-9) { 
        printf("n/a");
    } else {
        invert(matrix, rows);
    }

    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
    return 0;
}

void get_minor(double **matrix, double **minor, int row, int col, int n) {
    int i_m = 0, j_m = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        j_m = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            minor[i_m][j_m] = matrix[i][j];
            j_m++;
        }
        i_m++;
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

void invert(double **matrix, int n) {
    double det = determinant(matrix, n);
    double **res = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) res[i] = malloc(n * sizeof(double));

    if (n == 1) {
        res[0][0] = 1.0 / matrix[0][0];
    } else {
        double **minor = malloc((n - 1) * sizeof(double *));
        for (int i = 0; i < n - 1; i++) minor[i] = malloc((n - 1) * sizeof(double));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                get_minor(matrix, minor, i, j, n);
                
                res[j][i] = (pow(-1, i + j) * determinant(minor, n - 1)) / det;
            }
        }
        for (int i = 0; i < n - 1; i++) free(minor[i]);
        free(minor);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.6f", res[i][j]);
            if (j < n - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
        free(res[i]);
    }
    free(res);
}
