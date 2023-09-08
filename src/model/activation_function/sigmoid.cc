#include "sigmoid.h"

#include <algorithm>
#include <cmath>

void Sigmoid::ApplyActivationFunction(std::vector<double> &values) {
  std::transform(values.begin(), values.end(), values.begin(),
                 [](const double &el) { return 1.0 / (1.0 + exp(-el)); });
}

void Sigmoid::CalculateActivationFunctionDerivative(
    std::vector<double> &values) {
  std::transform(values.begin(), values.end(), values.begin(),
                 [](const double &el) { return el * (1.0 - el); });
}