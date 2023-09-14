#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <iostream>

#include "i_activation_function.h"
#include "picture.h"

class IPerceptron {
 public:
  virtual ~IPerceptron() = default;

  virtual void Configure(std::size_t input_layer_size,
                         std::size_t output_layer_size,
                         std::size_t hidden_layers_count,
                         std::size_t hidden_layers_size) = 0;

  virtual void SetTrainDataset(Dataset &dataset) = 0;
  virtual void SetTestDataset(Dataset &dataset) = 0;
  virtual void SetActivationFunction(
      IActivationFunction *activationFunction) = 0;

  virtual int Predict(Picture &picture) = 0;
  virtual void Train(std::size_t epochs) = 0;
  virtual void CrossValidation(std::size_t groups) = 0;

  virtual void LoadWeights(const std::istream &istream) = 0;
  virtual void ExportWeights(const std::ostream &ostream) = 0;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
