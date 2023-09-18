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
  MatrixPerceptron(Dataset *, Mapping *, int hidden_layers_count,
                   int size_hidden_layers);
  ~MatrixPerceptron() override = default;

  int Predict(const Picture &picture) override;
  void SetInput(const Picture &picture);
  void Train(int epochs) override;
  void LoadWeights(const std::string &file_path) override;
  void ExportWeights(const std::string &file_path) override;
  double TestMatrixPerceptron(const Dataset &test_dataset);

  void PrintPerceptronSetting() {
    std::cout << "===================PERCEPTRON SETTING=================="
              << std::endl;
    std::cout << "Layers size: " << number_of_layers_ << std::endl;
    for (int size_layer : size_layers_) {
      std::cout << size_layer << " ";
    }
    std::cout << "\n======================================================"
              << std::endl;
    for (const auto &size : neuron_values_) {
      std::cout << "Size :" << size.size() << std::endl;
    }
  }

  void PrintOutLayer() {
    for (const auto &el : neuron_values_[number_of_layers_ - 1]) {
      std::cout << el << std::endl;
    }
  }

  void PrintInputLayer() {
    for (std::size_t i = 0; i < neuron_values_[0].size(); ++i) {
      if (i % 28 == 0) {
        std::cout << std::endl;
      }
      std::cout << std::setw(4) << std::setprecision(2) << neuron_values_[0][i]
                << " ";
    }
  }
  int ForwardFeed();
  void BackPropagation(int);
  void UpdateWeights(double);
  void UpdateBiases(double);

 private:
  static bool IsValidDataForPerceptron(int, int);
  static int FindMaxIndex(const std::vector<double> &);

  void InitSizeLayers(int size_hidden);
  void InitRandomWeightsAndBiases();
  void InitNeuronsAndErr();

  static constexpr int kMinAmountOfHiddenLayers{2};
  static constexpr int kMaxAmountOfHiddenLayers{5};
  static constexpr double kStartLearningRate{0.14};
  static constexpr double kDecayRate{0.1};
  Dataset *dataset_;
  Mapping *mapping_;
  std::unique_ptr<IActivationFunction> activation_function_;

  int number_of_layers_{2};
  int epoch_ = 1;
  std::vector<int> size_layers_;
  std::vector<Matrix> weights_;
  std::vector<std::vector<double> > neuron_values_;
  std::vector<std::vector<double> > neuron_errors_;
  std::vector<std::vector<double> > biases_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
