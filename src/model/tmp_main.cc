#include <fstream>
#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"

int main() {
  Mapping mapping = Parser::ParseMapping(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-mapping.txt");

  Dataset dataset = Parser::ParseDataset(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-train.csv");

  std::cout << "START" << std::endl;

  MatrixPerceptron perceptron(&dataset, &mapping, 4, 256);

//  std::cout << "START TRAIN" << std::endl;
//  perceptron.Train(10);

//  perceptron.ExportWeights("Weight.txt");
  perceptron.LoadWeights("52%.txt");

  double right = perceptron.TestMatrixPerceptron(
      Parser::ParseDataset("/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/"
                           "datasets/emnist-letters/emnist-letters-test.csv"));

  std::cout << "FINAL RESULT: " << right << "%" << std::endl;

  return 1;
}
