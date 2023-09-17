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
  //
  //  std::cout << dataset.GetDataSize() << std::endl;

  Dataset test_data =
      Parser::ParseDataset("/Users/englishk/Desktop/emnist-letters-test.csv");

  perceptron.LoadWeights(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/src/model/"
      "20_epoch.txt");
  //  for (int i = 0; i < 20; ++i) {
  //    perceptron.Train(1);
      double right = perceptron.TestMatrixPerceptron(test_data);
      std::cout << "FINAL RESULT: " << right << "%" << std::endl;
  //  }

  //  perceptron.ExportWeights("20_epoch.txt");

  return 1;
}
