#ifndef __MATRIX_PERCEPTRON_H__
#define __MATRIX_PERCEPTRON_H__

#include "../lib/matrix.h"
#include "perceptron_interface.h"

class MatrixPerceptron : public PerceptronInterface {
 public:
 private:
  int number_of_layers_{2};
  std::vector<Matrix> weights_;
  Matrix neuron_values_;
  Matrix neuron_errors_;
};
#endif  // __MATRIX_PERCEPTRON_H__