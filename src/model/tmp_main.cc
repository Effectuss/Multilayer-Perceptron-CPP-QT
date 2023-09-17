#include <fstream>
#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"

int main() {
  Mapping mapping = Parser::ParseMapping(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-mapping.txt");

  Dataset dataset =
      Parser::ParseDataset("/Users/englishk/Desktop/emnist-letters-train.csv");

  std::cout << "START" << std::endl;

  MatrixPerceptron perceptron(&dataset, &mapping, 3, 144);

  std::cout << dataset.GetDataSize() << std::endl;

  Dataset test_data =
      Parser::ParseDataset("/Users/englishk/Desktop/emnist-letters-test.csv");

  for (int i = 0; i < 10; ++i) {
    perceptron.Train(1);
    double right = perceptron.TestMatrixPerceptron(test_data);
    std::cout << "FINAL RESULT: " << right << "%" << std::endl;
  }

  return 1;
}
