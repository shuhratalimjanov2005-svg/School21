#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double witch_agnesi(double x) { return 1.0 / (x * x + 1.0); }

double lemniscate(double x) {
    double inner = sqrt(0.25 + x * x);
    double val = inner - x * x - 0.25;
    return (val >= 0) ? sqrt(val) : -1.0;
}

double hyperbola(double x) { return (x != 0) ? 1.0 / (x * x) : -1.0; }

int main() {
    int width = 42;
    int height = 21;
    double start_x = -M_PI;
    double end_x = M_PI;
    double step_x = (end_x - start_x) / (width - 1);

for (int y_i = height - 1; y_i >= 0; y_i--) {
        double current_y = (double)y_i / (height - 1);

        for (int x_i = 0; x_i < width; x_i++) {
            double x = start_x + x_i * step_x;
            
            double f1 = witch_agnesi(x);
            double f2 = lemniscate(x);
            double f3 = hyperbola(x);

if (fabs(f1 - current_y) < 0.025 || 
                fabs(f2 - current_y) < 0.025 || 
                fabs(f3 - current_y) < 0.025) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
