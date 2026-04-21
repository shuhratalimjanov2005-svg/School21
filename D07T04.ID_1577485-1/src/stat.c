#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    output(data, n);
    printf("%d %d %.6f %.6f\n", max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    char c;
    if (scanf("%d%c", n, &c) != 2 || (*n <= 0 || *n > NMAX) || (c != ' ' && c != '\n')) {
        return 1;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    return 0;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

int max(int *a, int n) {
    int res = a[0];
    for (int i = 1; i < n; i++) if (a[i] > res) res = a[i];
    return res;
}

int min(int *a, int n) {
    int res = a[0];
    for (int i = 1; i < n; i++) if (a[i] < res) res = a[i];
    return res;
}

double mean(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double v = 0;
    for (int i = 0; i < n; i++) {
        v += (a[i] - m) * (a[i] - m);
    }
    return v / n;
}
