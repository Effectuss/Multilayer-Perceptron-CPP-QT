#include "matrix_perceptron.h"

#include <iomanip>
#include <utility>

MatrixPerceptron::MatrixPerceptron(Dataset dataset, Mapping mapping,
                                   int hidden_layers_count,
                                   int size_hidden_layers)
    : dataset_{std::move(dataset)}, mapping_{std::move(mapping)},
      activation_function_(std::make_unique<Sigmoid>()) {

  if (!IsValidDataForPerceptron(hidden_layers_count, size_hidden_layers)) {
    throw std::invalid_argument("Incorrect data for perceptron!");
  }

  number_of_layers_ = hidden_layers_count + 2;
}

bool MatrixPerceptron::IsValidDataForPerceptron(int hidden_layers_count,
                                                int size_hidden_layers) {
  return (hidden_layers_count <= kMaxAmountOfHiddenLayers &&
          hidden_layers_count >= kMinAmountOfHiddenLayers) &&
         size_hidden_layers > 0;
}
