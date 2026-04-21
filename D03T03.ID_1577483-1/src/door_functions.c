#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    double start = -M_PI;
    double end = M_PI;
    int steps = 42;
    
    double step = (end - start) / (steps - 1);

    for (int i = 0; i < steps; i++) {
        double x = start + i * step;
        
        
        double y1 = 1.0 / (x * x + 1.0);

        
        
        double inner_sqrt = sqrt(0.25 + x * x);
        double check = inner_sqrt - x * x - 0.25;
        
        
        double y3 = 1.0 / (x * x);

        
        printf("%.7f | ", x);

        
        printf("%.7f | ", y1);

        
       if (check < 0) {
            printf("- | ");
        } else {
            printf("%.7f | ", sqrt(check));
        }

       
       if (x == 0) {
            printf("-\n");
        } else {
            printf("%.7f\n", y3);
        }
    }

    return 0;
}
