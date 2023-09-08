#ifndef MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
#define MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H

#include "i_activation_function.h"

class Sigmoid : public IActivationFunction {
  void Apply(std::vector<double> &values) override;
  void CalculateDerivative(std::vector<double> &values) override;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
