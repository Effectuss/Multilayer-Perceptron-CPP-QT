#ifndef MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
#define MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H

#include <vector>

class IActivationFunction {
 public:
  virtual ~IActivationFunction() = 0;

  virtual void Apply(std::vector<double> &values) = 0;
  virtual void CalculateDerivative(std::vector<double> &values) = 0;
};

inline IActivationFunction::~IActivationFunction() {}

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
