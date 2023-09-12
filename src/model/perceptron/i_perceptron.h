#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <iostream>

#include "picture.h"

class IPerceptron {
 public:
  // вот такой конструктор в своем прецептроне в интерфейсе не надо
  //  MatrixPerceptron(Dataset, Mapping, int hidden_layers_count,
  //                   int size_hidden_layers);
  virtual ~IPerceptron() = 0;

  virtual int Predict(const Picture &picture) = 0;
  virtual void Train(int epochs) = 0;
  virtual void LoadWeights(const std::string &file_path) = 0;
  virtual void ExportWeights(const std::string &file_path) = 0;
};

inline IPerceptron::~IPerceptron() {}

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
