#include <iostream>

#include "parser.h"

int main() {
  Mapping mapping = Parser::ParseMapping(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-mapping.txt");
  //  for (auto &elem: mapping.GetItem(12)) {
  //    std::cout << elem << std::endl;
  //  }
  std::cout << mapping.GetDataSize();
  return 1;
}
