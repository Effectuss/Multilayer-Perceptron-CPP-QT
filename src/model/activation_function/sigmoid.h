#ifndef __SIGMOID_H__
#define __SIGMOID_H__

#include <algorithm>

#include "activation_function_interface.h"

class Sigmoid : public ActivationFunctionInterface {
 public:
  void ApplyActivationFunction(std::vector<double>& values) override;
  void CalculateActivationFunctionDerivative(
      std::vector<double>& values) override;
};

#endif  // __SIGMOID_H__