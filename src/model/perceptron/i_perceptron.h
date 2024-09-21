#ifndef MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H

#include <atomic>
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
  // std::shared_ptr<IActivationFunction> activation_function)
  virtual ~IPerceptron() = default;

  virtual std::vector<double> Predict(const Picture& picture) = 0;

  virtual void Train(std::size_t epochs, const Dataset& dataset) = 0;

  virtual void SetActivationFunction(
      std::shared_ptr<IActivationFunction> activation_function) = 0;

  virtual void LoadWeights(const std::string& file_name) = 0;
  virtual void ExportWeights(const std::string& file_name) = 0;

  void Cancel() { is_cancelled_ = true; }
  bool IsCancelled() const { return is_cancelled_; }
  bool IsFinished() const { return is_finished_; }

 protected:
  void Finish() { is_finished_ = true; }

 private:
  std::atomic<bool> is_cancelled_ = false;
  std::atomic<bool> is_finished_ = false;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_IPERCEPTRON_H
