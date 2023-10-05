#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <memory>
#include <string>
#include <vector>

#include "dataset.h"
#include "i_activation_function.h"
#include "picture.h"

class IPerceptron {
 public:
  // constructor (with 4 params)
  // SomePerceptron(
  // std::size_t hidden_layers_count,
  // std::size_t hidden_layers_size,
  // const Mapping &mapping
  // std::unique_ptr<IActivationFunction> &activationFunction)
  virtual ~IPerceptron() = default;

  virtual std::vector<double> Predict(const Picture& picture) = 0;

  virtual void Train(std::size_t epochs, const Dataset& dataset) = 0;
  virtual void Test(double segment, const Dataset& dataset) = 0;

  virtual void SetActivationFunction(
      std::unique_ptr<IActivationFunction>& activationFunction) = 0;

  virtual void LoadWeights(const std::string& file_name) = 0;
  virtual void ExportWeights(const std::string& file_name) = 0;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
