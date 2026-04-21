#include <stdio.h>
#include <stdlib.h>

int allocate(int ***matrix, int rows, int cols);
void free_matrix(int **matrix);
int input_matrix(int ***matrix, int *rows, int *cols);
void output(int **matrix, int rows, int cols);

void sum(int **A, int r1, int c1, int **B, int r2, int c2);
void mul(int **A, int r1, int c1, int **B, int r2, int c2);
void transpose(int **A, int r1, int c1);

int main() {
    int op;
    if (scanf("%d", &op) != 1 || op < 1 || op > 3) { printf("n/a"); return 0; }

    int **A = NULL, r1, c1;
    if (input_matrix(&A, &r1, &c1)) { printf("n/a"); return 0; }

    if (op == 1 || op == 2) {
        int **B = NULL, r2, c2;
        if (input_matrix(&B, &r2, &c2)) { 
            printf("n/a"); free_matrix(A); return 0; 
        }
        if (op == 1) sum(A, r1, c1, B, r2, c2);
        else mul(A, r1, c1, B, r2, c2);
        free_matrix(B);
    } else {
        transpose(A, r1, c1);
    }

    free_matrix(A);
    return 0;
}


void sum(int **A, int r1, int c1, int **B, int r2, int c2) {
    if (r1 != r2 || c1 != c2) { printf("n/a"); return; }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("%d", A[i][j] + B[i][j]);
            if (j < c1 - 1) printf(" ");
        }
        if (i < r1 - 1) printf("\n");
    }
}


void mul(int **A, int r1, int c1, int **B, int r2, int c2) {
    if (c1 != r2) { printf("n/a"); return; }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            int res = 0;
            for (int k = 0; k < c1; k++) res += A[i][k] * B[k][j];
            printf("%d", res);
            if (j < c2 - 1) printf(" ");
        }
        if (i < r1 - 1) printf("\n");
    }
}

void transpose(int **A, int r1, int c1) {
    for (int j = 0; j < c1; j++) {
        for (int i = 0; i < r1; i++) {
            printf("%d", A[i][j]);
            if (i < r1 - 1) printf(" ");
        }
        if (j < c1 - 1) printf("\n");
    }
}


int allocate(int ***matrix, int rows, int cols) {
    *matrix = (int **)malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (*matrix == NULL) return 1;
    int *ptr = (int *)(*matrix + rows);
    for (int i = 0; i < rows; i++) (*matrix)[i] = ptr + i * cols;
    return 0;
}

void free_matrix(int **matrix) { if (matrix) free(matrix); }

int input_matrix(int ***matrix, int *rows, int *cols) {
    if (scanf("%d %d", rows, cols) != 2 || *rows <= 0 || *cols <= 0) return 1;
    if (allocate(matrix, *rows, *cols)) return 1;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) return 1;
        }
    }
    return 0;
}
