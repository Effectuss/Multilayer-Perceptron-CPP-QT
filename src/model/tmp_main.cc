#include <fstream>
#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"

int main() {
  Dataset dataset = Parser::ParseDataset(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-train.csv");
  Mapping mapping = Parser::ParseMapping(
      "/opt/goinfre/englishk/Multilayer-Perceptron-CPP-QT/datasets/"
      "emnist-letters/emnist-letters-mapping.txt");

  MatrixPerceptron mat_pre(dataset, mapping, 2, 100);
  mat_pre.PrintPerceptronSetting();
  Picture picture;
  picture.SetData(dataset.GetData()[0].first.GetData());
  int i = mat_pre.Predict(picture);

  std::vector<double> sd{3.3, 3.1, 0.2, -13.3, 1};

  std::cout << "\nRESULT: " << (char)i << std::endl;

  mat_pre.PrintOutLayer();
  return 1;
}
