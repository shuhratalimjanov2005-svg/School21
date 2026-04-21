#include "data_stat.h"

double max(const double *data, int n) {
  double m = data[0];
  for (int i = 1; i < n; i++)
    if (data[i] > m)
      m = data[i];
  return m;
}

double min(const double *data, int n) {
  double m = data[0];
  for (int i = 1; i < n; i++)
    if (data[i] < m)
      m = data[i];
  return m;
}

double mean(const double *data, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++)
    sum += data[i];
  return sum / n;
}

double variance(const double *data, int n) {
  double m = mean(data, n);
  double v = 0;
  for (int i = 0; i < n; i++)
    v += (data[i] - m) * (data[i] - m);
  return v / n;
}
