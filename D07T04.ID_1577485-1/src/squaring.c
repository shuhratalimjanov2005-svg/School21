#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    
    
    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    squaring(data, n);
    output(data, n);

    return 0;
}


int input(int *a, int *n) {
    char c;
    
    if (scanf("%d%c", n, &c) != 2 || (*n <= 0 || *n > NMAX) || (c != ' ' && c != '\n')) {
        return 1;
    }

    
    for (int *p = a; p < a + *n; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }
    
    
    char end;
    if (scanf("%c", &end) == 1 && end != '\n' && end != ' ') {
         return 1;
    }

    return 0;
}


void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}


void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
