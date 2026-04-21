#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "../yet_another_decision_module/decision.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DYNAMIC
#include "../data_module/data_process.h"
#endif

int normalization(double *data, int n);

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

  printf("RAW DATA:\n");
  output(data, n);
  printf("\n");

  printf("NORMALIZED DATA:\n");
  normalization(data, n);
  output(data, n);
  printf("\n");

  printf("FINAL DECISION:\n");
  if (make_decision(data, n)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  free(data);
  return 0;
}
