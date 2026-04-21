#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int allocate_1(int ***matrix, int rows, int cols);
int allocate_2(int ***matrix, int rows, int cols);
int allocate_3(int ***matrix, int rows, int cols);
void free_matrix(int **matrix, int rows, int type);
void output(int **matrix, int rows, int cols);
void find_max_min(int **matrix, int rows, int cols);

int main() {
    int rows, cols, type, error = 0;
    int **matrix = NULL;
    static int static_matrix[MAX_SIZE][MAX_SIZE];
    int *static_ptr[MAX_SIZE];

    if (scanf("%d", &type) != 1 || type < 1 || type > 4) { printf("n/a"); return 0; }
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || (type == 1 && (rows > MAX_SIZE || cols > MAX_SIZE))) {
        printf("n/a"); return 0;
    }

    if (type == 1) {
        for (int i = 0; i < rows; i++) static_ptr[i] = static_matrix[i];
        matrix = static_ptr;
    } else if (type == 2) error = allocate_1(&matrix, rows, cols);
    else if (type == 3) error = allocate_2(&matrix, rows, cols);
    else if (type == 4) error = allocate_3(&matrix, rows, cols);

    if (error) { printf("n/a"); return 0; }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) { printf("n/a"); if (type != 1) free_matrix(matrix, rows, type); return 0; }
        }
    }

    output(matrix, rows, cols);
    printf("\n"); // Переход к выводу массивов
    find_max_min(matrix, rows, cols);

    if (type != 1) free_matrix(matrix, rows, type);
    return 0;
}

void find_max_min(int **matrix, int rows, int cols) {
    // Максимумы в строках
    for (int i = 0; i < rows; i++) {
        int max = matrix[i][0];
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] > max) max = matrix[i][j];
        }
        printf("%d", max);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    // Минимумы в столбцах
    for (int j = 0; j < cols; j++) {
        int min = matrix[0][j];
        for (int i = 1; i < rows; i++) {
            if (matrix[i][j] < min) min = matrix[i][j];
        }
        printf("%d", min);
        if (j < cols - 1) printf(" ");
    }
}

void output(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

// Функции аллокации (копируем из matrix.c)
int allocate_1(int ***matrix, int rows, int cols) {
    *matrix = (int **)malloc(rows * sizeof(int *));
    if (*matrix == NULL) return 1;
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = (int *)malloc(cols * sizeof(int));
        if ((*matrix)[i] == NULL) return 1;
    }
    return 0;
}
int allocate_2(int ***matrix, int rows, int cols) {
    *matrix = (int **)malloc(rows * sizeof(int *));
    int *values = (int *)malloc(rows * cols * sizeof(int));
    if (*matrix == NULL || values == NULL) return 1;
    for (int i = 0; i < rows; i++) (*matrix)[i] = values + i * cols;
    return 0;
}
int allocate_3(int ***matrix, int rows, int cols) {
    *matrix = (int **)malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (*matrix == NULL) return 1;
    int *ptr = (int *)(*matrix + rows);
    for (int i = 0; i < rows; i++) (*matrix)[i] = ptr + i * cols;
    return 0;
}
void free_matrix(int **matrix, int rows, int type) {
    if (type == 2) { for (int i = 0; i < rows; i++) free(matrix[i]); }
    else if (type == 3) { free(matrix[0]); }
    free(matrix);
}
