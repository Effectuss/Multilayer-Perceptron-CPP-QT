#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include <memory>

#include "dataset.h"
#include "i_perceptron.h"
#include "mapping.h"
#include "matrix.h"
#include "sigmoid.h"

class MatrixPerceptron final : public IPerceptron {
 public:
  MatrixPerceptron(Dataset, Mapping, int hidden_layers_count,
                   int size_hidden_layers);
  ~MatrixPerceptron() override = default;

  int Predict(Picture picture) override { return 1; }
  void Train(int epochs) override;
  void LoadWeights(const std::istream &) override {}
  void ExportWeights(const std::ostream &) override {}

  void PrintPerceptronSetting() {
    std::cout << "===================PERCEPTRON SETTING=================="
              << std::endl;
    std::cout << "Layers size: " << number_of_layers_ << std::endl;
    for (int size_layer : size_layers_) {
      std::cout << size_layer << " ";
    }
    std::cout << "\n======================================================"
              << std::endl;
  }

 private:
  static bool IsValidDataForPerceptron(int, int);

  void InitSizeLayers(int size_hidden);
  void InitRandomWeights();
  void InitMatricesNeurons();
  void ForwardFeed();

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

  // веса смещения biases
  std::vector<Matrix> biases_;

  // значение нейронов
  std::vector<Matrix> neuron_values_;

  // ошибки для нейронов
  std::vector<Matrix> neuron_errors_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
