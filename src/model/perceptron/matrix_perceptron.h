#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include "i_perceptron.h"
#include "matrix.h"

class MatrixPerceptron : public IPerceptron {
 public:
  MatrixPerceptron(int hidden_layers_count, int size_hidden_layers);

  void SetTrainDataset(Dataset& dataset) override;
  void SetActivationFunction(
      std::unique_ptr<IActivationFunction> function) override;

  void Train(int epochs) override;

 private:
  static constexpr int kMinAmountOfHiddenLayers{2};
  static constexpr int kMaxAmountOfHiddenLayers{5};

  static bool IsValidDataForPerceptron(int, int);

  void InitRandomWeights();
  void InitNeuronNetwork();
  void InitSizeLayers(int);

  int number_of_layers_{2};

  Dataset dataset_;

  std::unique_ptr<IActivationFunction> activation_function_;

  std::vector<int> size_layers_;
  std::vector<std::vector<double>> neuron_values_;
  std::vector<std::vector<double>> neuron_errors_;
  std::vector<std::vector<double>> delta_weight_;
  std::vector<Matrix> weights_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
