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

  MatrixPerceptron perceptron(dataset, mapping, 3, 100);
  perceptron.Train(2);
  perceptron.ExportWeights("Weight.txt");
  return 1;
}
