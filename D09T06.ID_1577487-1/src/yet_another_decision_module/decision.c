#include "decision.h"
#include "../data_libs/data_stat.h"
#include <math.h>

int make_decision(const double *data, int n) {
  int decision = 1;

  double m = mean(data, n);

  if (m < GOLDEN_RATIO) {
    decision = 0;
  }

  if (decision == 1) {
    double s = sqrt(variance(data, n));
    for (int i = 0; i < n; i++) {
      if (fabs(data[i] - m) > 3 * s) {
        decision = 0;
        break;
      }
    }
  }

  return decision;
}
