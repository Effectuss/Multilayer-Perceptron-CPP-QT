#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include <memory>

#include "i_perceptron.h"
#include "matrix.h"
#include "sigmoid.h"

class MatrixPerceptron : public IPerceptron {
public:
  MatrixPerceptron(Dataset, Mapping, int hidden_layers_count,
                   int size_hidden_layers);

private:
  static bool IsValidDataForPerceptron(int, int);
  void InitSizeLayers(int size_hidden);
  void InitRandomWeights();
  void InitMatricesNeurons();

  static constexpr int kMinAmountOfHiddenLayers{2};
  static constexpr int kMaxAmountOfHiddenLayers{5};

  Dataset dataset_;
  Mapping mapping_;
  std::unique_ptr<IActivationFunction> activation_function_;
  int number_of_layers_{2};
  std::vector<int> size_layers_;
  std::vector<Matrix> weights_;
  std::vector<Matrix> neuron_values_;
  std::vector<Matrix> neuron_errors_;
};

#endif // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
