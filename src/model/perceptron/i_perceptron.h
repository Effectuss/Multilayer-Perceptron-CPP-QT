#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <iostream>

#include "picture.h"

class IPerceptron {
  // вот такой конструктор в своем прецептроне в интерфейсе не надо
  //  MatrixPerceptron(Dataset, Mapping, int hidden_layers_count,
  //                   int size_hidden_layers);
protected:
  virtual ~IPerceptron() = default;

public:
  virtual int Predict(Picture picture) = 0;
  virtual void Train(int epochs) = 0;
  virtual void LoadWeights(const std::istream &) = 0;
  virtual void ExportWeights(const std::ostream &) = 0;
};

#endif // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
