#include <stdio.h>

#define NMAX 10

int input(int *a, int *n, int *c);
void output(int *a, int n);
void shift(int *a, int n, int c);

int main() {
    int n, data[NMAX], c;

    if (input(data, &n, &c) != 0) {
        printf("n/a\n");
        return 0;
    }

    shift(data, n, c);
    output(data, n);

    return 0;
}

int input(int *a, int *n, int *c) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX) return 1;
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    if (scanf("%d", c) != 1) return 1;
    return 0;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}


void shift(int *a, int n, int c) {
    
    c = c % n;
    if (c < 0) c = n + c; 

    for (int j = 0; j < c; j++) {
        int temp = a[0];
        for (int i = 0; i < n - 1; i++) {
            *(a + i) = *(a + i + 1);
        }
        *(a + n - 1) = temp;
    }
}
