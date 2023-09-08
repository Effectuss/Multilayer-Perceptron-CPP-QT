#include <iostream>

#include "parser.h"

int main() {
  Mapping mapping = Parser::ParseMapping(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-mapping.txt");
  std::cout << mapping.GetDataSize();
  return 1;
}