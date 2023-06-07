#include "matrix_perceptron.h"

MatrixPerceptron::MatrixPerceptron(int hidden_layers_count,
                                   int size_hidden_layers)
    : number_of_layers_{hidden_layers_count + 2},
      activation_function_(std::make_unique<Sigmoid>()) {
  InitSizeLayers(size_hidden_layers);
  InitRandomWeights();
  InitMatricesNeurons();
}

void MatrixPerceptron::InitSizeLayers(int size_hidden) {
  for (int i = 0; i < number_of_layers_; ++i) {
    if (i == 0) {
      size_layers_.push_back(size_input_lauer_);
    } else if (i == number_of_layers_ - 1) {
      size_layers_.push_back(size_out_lauer_);
    } else {
      size_layers_.push_back(size_hidden);
    }
  }
}

void MatrixPerceptron::InitRandomWeights() {
  weights_.resize(number_of_layers_ - 1);
  for (int i = 0; i < number_of_layers_ - 1; ++i) {
    weights_[i] = std::move(Matrix(size_layers_[i], size_layers_[i]));
    weights_[i].FillMatrixRandomValues();
  }
}

void MatrixPerceptron::InitMatricesNeurons() {
  for (int i = 0; i < number_of_layers_; ++i) {
  }
}