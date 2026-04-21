#include <stdio.h>
#include <math.h>

#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int search(int *a, int n, double m, double v);

int main() {
    int n, data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    double m = mean(data, n);
    double v = variance(data, n);

    printf("%d\n", search(data, n, m, v));

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

double mean(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double v = 0;
    for (int i = 0; i < n; i++) v += (a[i] - m) * (a[i] - m);
    return v / n;
}


int search(int *a, int n, double m, double v) {
    double sigma = sqrt(v);
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 &&             
            a[i] >= m &&                 
            a[i] != 0 &&                 
            a[i] >= (m - 3 * sigma) &&   
            a[i] <= (m + 3 * sigma)) {   
            
            result = a[i];
            break; 
        }
    }
    return result;
}
