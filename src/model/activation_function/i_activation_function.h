#ifndef MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
#define MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H

class IActivationFunction {
 public:
  virtual ~IActivationFunction() = 0;
  virtual void ApplyActivationFunction(std::vector<double>& values) = 0;
  virtual void CalculateActivationFunctionDerivative(
      std::vector<double>& values) = 0;
};

IActivationFunction::~IActivationFunction() = default;

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
