#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"
#include "sigmoid.h"

int main() {
  std::unique_ptr<IActivationFunction> sigmoid = std::make_unique<Sigmoid>();

  Dataset dataset = Parser::ParseDataset(
      "/Users/englishk/goinfre/emnist-letters/emnist-letters-train.csv");
  Dataset train_dataset = Parser::ParseDataset(
      "/Users/englishk/goinfre/emnist-letters/emnist-letters-test.csv");

  MatrixPerceptron perceptron(3, 144);

  perceptron.SetTrainDataset(dataset);
  perceptron.SetActivationFunction(sigmoid);

    perceptron.LoadWeights("/Users/englishk/goinfre/weight.txt");

  //  for (int i = 0; i < 1; ++i) {
//      perceptron.Train(1);
  double r_p = perceptron.TestMatrixPerceptron(train_dataset);
  std::cout << "AFTER TEST: " << r_p << "%" << std::endl;
  //  }

//  perceptron.ExportWeights("/Users/englishk/goinfre/weight.txt");

  return 1;
}
