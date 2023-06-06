#ifndef __ACTIVATION_FUNCTION_H__
#define __ACTIVATION_FUNCTION_H__

#include <cmath>
#include <vector>

class ActivationFunctionInterface {
 public:
  virtual ~ActivationFunctionInterface() = 0;
  virtual void ApplyActivationFunction(std::vector<double> &values) = 0;
  virtual void CalculateActivationFunctionDerivative(
      std::vector<double>& values) = 0;
};

#endif  // __ACTIVATION_FUNCTION_H__