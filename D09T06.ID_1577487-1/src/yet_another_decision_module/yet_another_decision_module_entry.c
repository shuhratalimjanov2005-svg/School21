#include "../data_libs/data_io.h"
#include "decision.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  double *data;
  int n;

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("n/a");
    return 0;
  }

  data = (double *)malloc(n * sizeof(double));
  if (data == NULL) {
    printf("n/a");
    return 0;
  }

  input(data, n);

  if (make_decision(data, n)) {
    printf("YES\n");
  } else {
    printf("NO");
  }

  free(data);

  return 0;
}
