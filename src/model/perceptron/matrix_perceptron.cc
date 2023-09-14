#include "matrix_perceptron.h"

bool MatrixPerceptron::IsValidDataForPerceptron(int hidden_layers_count,
                                                int size_hidden_layers) {
  return (hidden_layers_count <= kMaxAmountOfHiddenLayers &&
          hidden_layers_count >= kMinAmountOfHiddenLayers) &&
         size_hidden_layers > 0;
}

MatrixPerceptron::MatrixPerceptron(int hidden_layers_count,
                                   int size_hidden_layers) {
  if (!IsValidDataForPerceptron(hidden_layers_count, size_hidden_layers)) {
    throw std::invalid_argument("Incorrect data for perceptron!");
  }

  number_of_layers_ = hidden_layers_count + 2;

  InitSizeLayers(size_hidden_layers);
  InitRandomWeights();
  InitNeuronNetwork();
}

void MatrixPerceptron::InitSizeLayers(int size_hidden) {
  for (int i = 0; i < number_of_layers_; ++i) {
    if (i == 0) {
      // todo magic number
      size_layers_.push_back(784);
    } else if (i == number_of_layers_ - 1) {
      // todo magic number
      size_layers_.push_back(26);
    } else {
      size_layers_.push_back(size_hidden);
    }
  }
}

void MatrixPerceptron::InitRandomWeights() {
  weights_.resize(number_of_layers_ - 1);

  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    weights_[i] = std::move(Matrix(size_layers_[i + 1], size_layers_[i]));
    weights_[i].FillMatrixRandomValues();
  }
}

void MatrixPerceptron::InitNeuronNetwork() {
  for (int i = 0; i < number_of_layers_; ++i) {
    neuron_values_.emplace_back(size_layers_[i]);
    neuron_errors_.emplace_back(size_layers_[i]);
    delta_weight_.emplace_back(size_layers_[i]);
  }
}

void MatrixPerceptron::SetActivationFunction(
    std::unique_ptr<IActivationFunction>& function) {
  activation_function_ = std::move(function);
}

void MatrixPerceptron::SetTrainDataset(Dataset& dataset) { dataset_ = dataset; }

void MatrixPerceptron::Train(int epochs) {}

int MatrixPerceptron::ForwardFeed() {
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    Matrix::MultiplyByVector(weights_[i], neuron_values_[i],
                             neuron_values_[i + 1]);
    activation_function_->Activate(neuron_values_[i + 1]);
  }
  return FindMaxIndex(neuron_values_[number_of_layers_ - 1]);
}

int MatrixPerceptron::FindMaxIndex(const std::vector<double>& vector) {
  if (vector.empty()) return 0;

  int max_index = 0;
  for (int i = 0; i < vector.size(); ++i) {
    if (vector[i] >= vector[max_index]) {
      max_index = i;
    }
  }
  return max_index;
}

void MatrixPerceptron::SetInputLayer(const Picture& picture) {
  if (picture.GetSize() != neuron_values_[0].size()) {
    throw std::runtime_error("Invalid picture for input layer!");
  }

  neuron_values_[0] = picture.GetData();
}
