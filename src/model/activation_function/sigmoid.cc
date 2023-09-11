#include "sigmoid.h"

#include <algorithm>
#include <cmath>

void Sigmoid::Activate(std::vector<double> &values) {
  std::transform(values.begin(), values.end(), values.begin(),
                 [](const double &el) { return 1.0 / (1.0 + exp(-el)); });
}

void Sigmoid::Derivative(std::vector<double> &values) {
  std::transform(values.begin(), values.end(), values.begin(),
                 [](const double &el) { return el * (1.0 - el); });
}

double Sigmoid::Activate(double value) {
  return 1.0 / (1.0 + std::exp(-value));
}

double Sigmoid::Derivative(double value) { return value * (1.0 - value); }