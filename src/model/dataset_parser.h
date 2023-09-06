#ifndef _MULTILAYER_PERCEPTRON_CPP_QT_DATASET_PARSER_H_
#define _MULTILAYER_PERCEPTRON_CPP_QT_DATASET_PARSER_H_

#include <string>

#include "dataset.h"

class DatasetParser {
 public:
  static Dataset Parse(const std::string&);

 private:
  static int FindOutputLayerSize(const std::string&);
  static bool CheckEmnistDataset(const std::string&);
};

#endif  // _MULTILAYER_PERCEPTRON_CPP_QT_DATASET_PARSER_H_
