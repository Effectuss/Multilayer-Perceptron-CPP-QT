#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPARSER_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPARSER_H

#include <string>

#include "dataset.h"
#include "mapping.h"

class Parser {
 public:
  static Dataset ParseDataset(const std::string &);
  static Mapping ParseMapping(const std::string &);
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPARSER_H
