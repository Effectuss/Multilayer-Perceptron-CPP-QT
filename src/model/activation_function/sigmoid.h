#ifndef MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
#define MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H

#include "i_activation_function.h"

class Sigmoid : public IActivationFunction {
  double Activate(double value) override;
  void Activate(std::vector<double> &values) override;
  double Derivative(double value) override;
  void Derivative(std::vector<double> &values) override;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
