#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include "i_perceptron.h"
#include "matrix.h"
#include <iomanip>

class MatrixPerceptron : public IPerceptron {
 public:
  MatrixPerceptron(int hidden_layers_count, int size_hidden_layers);

  void SetInputLayer(const Picture& picture);
  void SetTrainDataset(Dataset& dataset) override;
  void SetActivationFunction(
      std::unique_ptr<IActivationFunction>& function) override;

  void Train(int epochs) override;

  // todo move to private
  int ForwardFeed();

  // todo delete debug method
  inline void PrintOutLayer() {
    for (const auto& el : neuron_values_[number_of_layers_ - 1]) {
      std::cout << el << std::endl;
    }
  }

  void PrintPerceptronSetting() {
    std::cout << "===================PERCEPTRON SETTING=================="
              << std::endl;
    std::cout << "Layers size: " << number_of_layers_ << std::endl;
    for (int size_layer : size_layers_) {
      std::cout << size_layer << " ";
    }
    std::cout << "\n======================================================"
              << std::endl;
    for (const auto& size : neuron_values_) {
      std::cout << "Size :" << size.size() << std::endl;
    }
  }

  void PrintInputLayer() {
    for (int i = 0; i < neuron_values_[0].size(); ++i) {
      if (i % 28 == 0) {
        std::cout << std::endl;
      }
      std::cout << std::setw(4) << std::setprecision(2) << neuron_values_[0][i]
                << " ";
    }
  }

 private:
  static constexpr int kMinAmountOfHiddenLayers{2};
  static constexpr int kMaxAmountOfHiddenLayers{5};

  static bool IsValidDataForPerceptron(int, int);

  void InitRandomWeights();
  void InitNeuronNetwork();
  void InitSizeLayers(int);

  static int FindMaxIndex(const std::vector<double>& vector);

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
