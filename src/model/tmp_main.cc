#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"
#include "sigmoid.h"

int main() {
  std::unique_ptr<IActivationFunction> sigmoid = std::make_unique<Sigmoid>();

  Dataset dataset = Parser::ParseDataset(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-test.csv");

  MatrixPerceptron perceptron(2, 144);

  perceptron.SetTrainDataset(dataset);
  perceptron.SetActivationFunction(sigmoid);

  perceptron.SetInputLayer(dataset.GetData()[0].first);

  perceptron.PrintInputLayer();

  perceptron.ForwardFeed();

  perceptron.PrintOutLayer();
  return 1;
}
