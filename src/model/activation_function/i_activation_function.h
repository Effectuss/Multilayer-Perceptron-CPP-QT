#ifndef MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
#define MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H

#include <vector>

class IActivationFunction {
 public:
  virtual ~IActivationFunction() = default;

  virtual double Activate(double value) = 0;
  virtual void Activate(std::vector<double> &values) = 0;
  virtual double Derivative(double value) = 0;
  virtual void Derivative(std::vector<double> &values) = 0;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_I_ACTIVATION_FUNCTION_H
