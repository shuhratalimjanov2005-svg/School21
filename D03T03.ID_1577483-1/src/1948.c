#include <stdio.h>


int get_remainder(int n, int d) {
    if (n < 0) n = -n;
    if (d < 0) d = -d;
    while (n >= d) {
        n -= d;
    }
    return n;
}


int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (get_remainder(n, i) == 0) {
            return 0; 
        }
    }
    return 1; 
}

int find_max_prime(int n) {
    if (n < 0) n = -n;
    int max_p = -1;
    for (int i = 2; i <= n; i++) {
        if (get_remainder(n, i) == 0) {
            if (is_prime(i)) {
                max_p = i;
            }
        }
    }
    return max_p;
}


int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a\n");
    } else {
        int result = find_max_prime(n);
        if (result == -1) {
            printf("n/a\n"); 
        } else {
            printf("%d\n", result);
        }
    }
    return 0; 
}
