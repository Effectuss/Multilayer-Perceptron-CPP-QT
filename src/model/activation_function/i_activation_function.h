#ifndef MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
#define MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H

#include <vector>

class IActivationFunction {
protected:
  virtual ~IActivationFunction() = default;

public:
  virtual void ApplyActivationFunction(std::vector<double> &values) = 0;
  virtual void
  CalculateActivationFunctionDerivative(std::vector<double> &values) = 0;
};

#endif // MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
