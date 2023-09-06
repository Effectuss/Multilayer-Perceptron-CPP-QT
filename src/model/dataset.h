#ifndef MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H
#define MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H

#include <utility>

#include "picture.h"

class Dataset {
 public:
  void AppendPair(const std::pair<Picture, int>&);
  void SetSizeOutputLayers(int);
  int GetSizeOutputLayers() const;
  int GetSizeDataset() const;

 private:
  std::vector<std::pair<Picture, int> > data_;
  int size_output_layers_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_DATASET_H
