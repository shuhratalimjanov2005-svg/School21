#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);

    make_picture(picture, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", picture[i][j]);
            if (j < M - 1) printf(" ");
        }
        if (i < N - 1) printf("\n");
    }

    return 0;
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int tree_trunk[] = { 7, 7, 7, 7 };
    int tree_foliage[] = { 3, 3, 3, 3 };
    int sun_data[6][5] = { { 0, 6, 6, 6, 6 }, 
                           { 0, 0, 6, 6, 6 }, 
                           { 0, 0, 6, 6, 6 },
                           { 0, 6, 0, 0, 6 },
                           { 0, 0, 0, 0, 0 },
                           { 0, 0, 0, 0, 0 } };

    reset_picture(picture, n, m);

    
    for (int i = 0; i < m; i++) {
        picture[0][i] = frame_w[i];
        picture[n - 1][i] = frame_w[i];
    }
    for (int i = 0; i < n; i++) {
        picture[i][0] = frame_h[i];
        picture[i][m - 1] = frame_h[i];
    }

  
    picture[2][3] = tree_foliage[0];
    picture[2][4] = tree_foliage[1];
    picture[3][2] = tree_foliage[2];
    picture[3][5] = tree_foliage[3];
    for (int j = 2; j <= 5; j++) picture[4][j] = 3;

    
    picture[10][3] = tree_trunk[0];
    picture[10][4] = tree_trunk[1];
    picture[6][3] = tree_trunk[2];
    picture[6][4] = tree_trunk[3];
    for (int i = 7; i <= 9; i++) {
        picture[i][3] = 7;
        picture[i][4] = 7;
    }

    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (sun_data[i][j] != 0) {
                picture[i + 1][j + 7] = sun_data[i][j];
            }
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {  
    for(int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}
