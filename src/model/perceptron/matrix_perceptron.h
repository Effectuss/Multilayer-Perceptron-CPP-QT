#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include <memory>

#include "dataset.h"
#include "i_perceptron.h"
#include "mapping.h"
#include "matrix.h"
#include "sigmoid.h"

class MatrixPerceptron : public IPerceptron {
 public:
  MatrixPerceptron(Dataset, Mapping, int hidden_layers_count,
                   int size_hidden_layers);
  ~MatrixPerceptron() override = default;

 private:
  static bool IsValidDataForPerceptron(int, int);

  static constexpr int kMinAmountOfHiddenLayers{2};
  static constexpr int kMaxAmountOfHiddenLayers{5};

  Dataset dataset_;
  Mapping mapping_;
  std::unique_ptr<IActivationFunction> activation_function_;
  // количество слоев
  int number_of_layers_{2};
  //  сколько нейронов на каждом слое
  std::vector<int> size_layers_;
  // матрица весов
  std::vector<Matrix> weights_;
  // значение нейронов
  std::vector<Matrix> neuron_values_;
  // ошибки для нейронов
  std::vector<Matrix> neuron_errors_;
  // веса смещения biases
  Matrix delta_weights_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
