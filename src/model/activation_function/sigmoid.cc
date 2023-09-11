#include "sigmoid.h"

#include <cmath>

double Sigmoid::Activate(double value) {
  return 1.0 / (1.0 + std::exp(-value));
}

double Sigmoid::Derivative(double value) { return value * (1.0 - value); }
