#include <fstream>
#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"

int main() {
  Matrix m(3, 3);
  m.FillMatrixRandomValues();
  std::cout << m;

  std::ifstream in_file(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/src/model/"
      "matrix.txt");
  in_file >> m;

  std::ofstream out_file(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/src/model/"
      "matrix_out.txt");
  out_file << m;

  std::cout << m;
  return 1;
}
