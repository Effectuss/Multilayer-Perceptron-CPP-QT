#include <iostream>

#include "dataset_parser.h"

int main() {
  auto dataset = DatasetParser::Parse(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-train.csv");
  std::cout << dataset.GetSizeDataset();
  return 1;
}