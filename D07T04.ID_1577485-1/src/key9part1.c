#include <stdio.h>

#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *pointers);

int main() {
    int n, data[NMAX];
    int result_data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    int sum = sum_numbers(data, n);
    
    
    if (sum == 0) {
        printf("n/a\n");
    } else {
        int result_length = find_numbers(data, n, sum, result_data);
        printf("%d\n", sum);
        output(result_data, result_length);
    }

    return 0;
}

int input(int *buffer, int *length) {
    char c;
    if (scanf("%d%c", length, &c) != 2 || *length <= 0 || *length > NMAX || (c != ' ' && c != '\n')) {
        return 1;
    }
    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) return 1;
    }
    return 0;
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < length - 1) printf(" ");
    }
    printf("\n");
}


int sum_numbers(int *buffer, int length) {
    int sum = 0;
    int has_even = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
            has_even = 1;
        }
    }
    return has_even ? sum : 0;
}


int find_numbers(int *buffer, int length, int number, int *pointers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            pointers[count] = buffer[i];
            count++;
        }
    }
    return count;
}
