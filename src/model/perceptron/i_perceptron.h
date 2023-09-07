#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <iostream>

#include "../data/dataset.h"
#include "../data/picture.h"

class IPerceptron {
 public:
  // IPerceptron (Dataset, Mapping, number of hidden 2-5, size of hidden > 0)
  virtual int Predict(Picture picture) = 0;
  virtual void Train() = 0;
  virtual void LoadWeights(const std::istream&) = 0;
  virtual void ExportWeights(const std::ostream&) = 0;
  // virtual void SetDataset(Dataset dataset) = 0;
  // virtual void SetMapping(Mapping mapping) = 0;

 private:
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H