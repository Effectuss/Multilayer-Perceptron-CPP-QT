#include "matrix_perceptron.h"

#include <algorithm>
#include <utility>

MatrixPerceptron::MatrixPerceptron(Dataset dataset, Mapping mapping,
                                   int hidden_layers_count,
                                   int size_hidden_layers)
    : dataset_{std::move(dataset)},
      mapping_{std::move(mapping)},
      activation_function_(std::make_unique<Sigmoid>()) {
  if (!IsValidDataForPerceptron(hidden_layers_count, size_hidden_layers)) {
    throw std::invalid_argument("Incorrect data for perceptron!");
  }

  number_of_layers_ = hidden_layers_count + 2;

  InitSizeLayers(size_hidden_layers);
  InitRandomWeightsAndBiases();
  InitNeuronsAndErr();
}

void MatrixPerceptron::InitSizeLayers(int size_hidden) {
  for (int i = 0; i < number_of_layers_; ++i) {
    if (i == 0) {
      size_layers_.push_back(
          static_cast<int>(dataset_.GetData()[i].first.GetSize()));
    } else if (i == number_of_layers_ - 1) {
      size_layers_.push_back(static_cast<int>(mapping_.GetDataSize()));
    } else {
      size_layers_.push_back(size_hidden);
    }
  }
}

void MatrixPerceptron::InitRandomWeightsAndBiases() {
  weights_.resize(number_of_layers_ - 1);
  biases_.resize(number_of_layers_ - 1);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> bias_distribution(-0.01, 0.01);

  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    weights_[i] = std::move(Matrix(size_layers_[i + 1], size_layers_[i]));
    weights_[i].FillMatrixRandomValues();
    biases_[i].resize(size_layers_[i + 1]);

    for (int j = 0; j < size_layers_[i + 1]; ++j) {
      biases_[i][j] = bias_distribution(gen);
    }
  }
}

void MatrixPerceptron::InitNeuronsAndErr() {
  for (int i = 0; i < number_of_layers_; ++i) {
    neuron_values_.emplace_back(size_layers_[i]);
    neuron_errors_.emplace_back(size_layers_[i]);
  }
}

bool MatrixPerceptron::IsValidDataForPerceptron(int hidden_layers_count,
                                                int size_hidden_layers) {
  return (hidden_layers_count <= kMaxAmountOfHiddenLayers &&
          hidden_layers_count >= kMinAmountOfHiddenLayers) &&
         size_hidden_layers > 0;
}

int MatrixPerceptron::ForwardFeed() {
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    neuron_values_[i + 1] = weights_[i] * neuron_values_[i];
    Matrix::SumVector(neuron_values_[i + 1], biases_[i]);
    activation_function_->Activate(neuron_values_[i + 1]);
  }
  return FindMaxIndex(neuron_values_[number_of_layers_ - 1]);
}

int MatrixPerceptron::Predict(Picture picture) {
  neuron_values_[0] = picture.GetData();
  int max_index = ForwardFeed();
  std::cout << max_index;
  return *mapping_.GetData()[max_index + 1].begin();
}

int MatrixPerceptron::FindMaxIndex(const std::vector<double>& vector) {
  if (vector.empty()) {
    return 0;
  }

  auto max_element = std::max_element(vector.begin(), vector.end());
  auto max_index = std::distance(vector.begin(), max_element);

  return static_cast<int>(max_index);
}

void MatrixPerceptron::BackPropagation(int expect) {
  for (int i = 0; i < size_layers_[number_of_layers_ - 1]; ++i) {
    if (i != expect) {
      neuron_errors_[number_of_layers_ - 1][i] =
          -neuron_values_[number_of_layers_ - 1][i] *
          activation_function_->Derivative(
              neuron_values_[number_of_layers_ - 1][i]);
    } else {
      neuron_errors_[number_of_layers_ - 1][i] =
          (1.0 - neuron_values_[number_of_layers_ - 1][i]) *
          activation_function_->Derivative(
              neuron_values_[number_of_layers_ - 1][i]);
    }
  }

  for (int k = number_of_layers_ - 2; k < 0; --k) {
    Matrix trans_weight = weights_[k];
    neuron_errors_[k] = trans_weight.MultiplyByVector(neuron_errors_[k + 1]);
    for (int j = 0; j < size_layers_[k]; ++j) {
      neuron_errors_[k][j] *=
          activation_function_->Derivative(neuron_values_[k][j]);
    }
  }
}

void MatrixPerceptron::UpdateWeights(double learning_rate) {
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    for (int j = 0; j < size_layers_[i + 1]; ++j) {
      for (int k = 0; k < size_layers_[i]; ++k) {
        weights_[i](j, k) +=
            neuron_values_[i][k] * neuron_errors_[i + 1][j] * learning_rate;
      }
    }
  }
}

void MatrixPerceptron::UpdateBiases(double learning_rate) {
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    for (int k = 0; k < size_layers_[i + 1]; ++k) {
      biases_[i][k] += neuron_errors_[i + 1][k] * learning_rate;
    }
  }
}

void MatrixPerceptron::Train(int epochs) {}

void MatrixPerceptron::LoadWeights(const std::istream&) {}

void MatrixPerceptron::ExportWeights(const std::ostream&) {}
