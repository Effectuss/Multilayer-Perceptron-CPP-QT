#ifndef MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H
#define MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H

#include <utility>

#include "picture.h"

class Dataset {
 public:
  void AppendDataToVector(const std::pair<Picture, int>&);
  int GetDataSize() const;
  std::vector<std::pair<Picture, int> > GetData() const;

 private:
  std::vector<std::pair<Picture, int> > data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H
