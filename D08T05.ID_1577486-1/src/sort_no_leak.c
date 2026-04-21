#include <stdio.h>
#include <stdlib.h> 

int main() {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    }

    
    int *data = (int *)malloc(n * sizeof(int));
    if (data == NULL) {
        printf("n/a");
        return 0;
    }

    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &data[i]) != 1) {
            printf("n/a");
            free(data); 
            return 0;
        }
    }

   
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i < n - 1) printf(" ");
    }

    
    free(data);

    return 0;
}
