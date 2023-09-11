#ifndef MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
#define MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H

#include "i_activation_function.h"

class Sigmoid : public IActivationFunction {
  double Activate(double value) override;
  double Derivative(double value) override;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_SIGMOID_H
