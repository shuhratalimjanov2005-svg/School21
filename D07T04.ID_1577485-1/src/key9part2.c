#include <stdio.h>

#define LEN 100

int input(int *a, int *len);
void output(int *a, int len);
void sum(int *a1, int len1, int *a2, int len2, int *result, int *res_len);
int sub(int *a1, int len1, int *a2, int len2, int *result, int *res_len);

int main() {
    int n1, n2, a1[LEN], a2[LEN];
    int res_sum[LEN + 1], res_sub[LEN];
    int len_sum, len_sub;

    if (input(a1, &n1) != 0 || input(a2, &n2) != 0) {
        printf("n/a\n");
        return 0;
    }

    sum(a1, n1, a2, n2, res_sum, &len_sum);
    output(res_sum, len_sum);

    if (sub(a1, n1, a2, n2, res_sub, &len_sub) != 0) {
        printf("n/a\n");
    } else {
        output(res_sub, len_sub);
    }

    return 0;
}

int input(int *a, int *len) {
    int i = 0;
    char c;
    while (scanf("%d%c", &a[i], &c) == 2) {
        if (a[i] < 0 || a[i] > 9) return 1;
        i++;
        if (c == '\n' || i >= LEN) break;
    }
    *len = i;
    return (i == 0);
}

void output(int *a, int len) {
    int start = 0;
    while (start < len - 1 && a[start] == 0) start++; 
    for (int i = start; i < len; i++) {
        printf("%d", a[i]);
        if (i < len - 1) printf(" ");
    }
    printf("\n");
}

void sum(int *a1, int len1, int *a2, int len2, int *result, int *res_len) {
    int i = len1 - 1, j = len2 - 1, k = (len1 > len2 ? len1 : len2);
    int carry = 0;
    *res_len = k + 1;
    result[0] = 0;

    while (k >= 0) {
        int v1 = (i >= 0) ? a1[i--] : 0;
        int v2 = (j >= 0) ? a2[j--] : 0;
        int s = v1 + v2 + carry;
        result[k--] = s % 10;
        carry = s / 10;
    }
    if (result[0] == 0) {
        for (int m = 0; m < *res_len - 1; m++) result[m] = result[m+1];
        (*res_len)--;
    }
}

int sub(int *a1, int len1, int *a2, int len2, int *result, int *res_len) {
    if (len2 > len1) return 1;
    if (len1 == len2) {
        int idx = 0;
        while (idx < len1 && a1[idx] == a2[idx]) idx++;
        if (idx < len1 && a2[idx] > a1[idx]) return 1;
    }
    
    int i = len1 - 1, j = len2 - 1, k = len1 - 1;
    int borrow = 0;
    *res_len = len1;

    while (i >= 0) {
        int v1 = a1[i--];
        int v2 = (j >= 0) ? a2[j--] : 0;
        int s = v1 - v2 - borrow;
        if (s < 0) {
            s += 10;
            borrow = 1;
        } else borrow = 0;
        result[k--] = s;
    }
    return 0;
}
