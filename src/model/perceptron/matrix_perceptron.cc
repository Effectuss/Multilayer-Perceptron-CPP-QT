#include "matrix_perceptron.h"

#include <algorithm>
#include <iomanip>
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

  // todo random bias
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    weights_[i] = std::move(Matrix(size_layers_[i + 1], size_layers_[i]));
    weights_[i].FillMatrixRandomValues();
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

void MatrixPerceptron::Train(int epochs) {}

int MatrixPerceptron::ForwardFeed() {
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    neuron_values_[i + 1] = weights_[i] * neuron_values_[i];
    activation_function_->Activate(neuron_values_[i + 1]);
  }
  return FindMaxIndex(neuron_values_[number_of_layers_ - 1]);
}

int MatrixPerceptron::Predict(Picture picture) {
  neuron_values_[0] = picture.GetData();
  int max_index = ForwardFeed();
  return *mapping_.GetData()[max_index].begin();
}

int MatrixPerceptron::FindMaxIndex(const std::vector<double>& vector) {
  if (vector.empty()) {
    return 0;
  }

  auto max_element = std::max_element(vector.begin(), vector.end());
  auto max_index = std::distance(vector.begin(), max_element);

  return static_cast<int>(max_index);
}

void MatrixPerceptron::BackPropagation() {}
