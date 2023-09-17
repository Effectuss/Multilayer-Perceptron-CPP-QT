#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"
#include "sigmoid.h"

int main() {
  std::unique_ptr<IActivationFunction> sigmoid = std::make_unique<Sigmoid>();

//  Dataset dataset = Parser::ParseDataset(
//      "/Users/englishk/Desktop/emnist-letters-test copy.csv");
//  Dataset train_dataset = Parser::ParseDataset(
//      "/Users/englishk/Desktop/emnist-letters-test copy.csv");

  Dataset dataset = Parser::ParseDataset(
      "/Users/englishk/Desktop/emnist-letters-train.csv");
  Dataset train_dataset = Parser::ParseDataset(
      "/Users/englishk/Desktop/emnist-letters-test.csv");

  MatrixPerceptron perceptron(3, 144);

  perceptron.SetTrainDataset(dataset);
  perceptron.SetActivationFunction(sigmoid);

    for (int i = 0; i < 5; ++i) {
  perceptron.Train(1);
      double r_p = perceptron.TestMatrixPerceptron(train_dataset);
      std::cout << "AFTER TEST: " << r_p << "%" << std::endl;
    }

  return 1;
}
