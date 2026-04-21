#include <stdio.h>

#define N 10

int input(int *a);
void sort(int *a);
void output(int *a);

int main() {
    int data[N];

    if (input(data) != 0) {
        printf("n/a\n");
        return 0;
    }

    sort(data);
    output(data);

    return 0;
}

int input(int *a) {
    char c;
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    
    if (scanf("%c", &c) == 1 && c != '\n' && c != ' ') return 1;
    
    return 0;
}

void sort(int *a) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (a[j] > a[j + 1]) {
               
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void output(int *a) {
    for (int i = 0; i < N; i++) {
        printf("%d", a[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");
}
