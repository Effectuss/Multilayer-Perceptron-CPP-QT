#ifndef MLP_LAYER_H_
#define MLP_LAYER_H_

#include "neuron.h"

class Layer final {
 public:
  Layer() = delete;
  explicit Layer(std::size_t number_of_neurons);
  Layer(const Layer &other) = default;
  Layer(Layer &&other) = default;
  Layer &operator=(const Layer &other) = default;
  Layer &operator=(Layer &&other) = default;
  ~Layer() = default;

  Layer &ConnectPrevious(const Layer &other);
  Layer &GenerateWeights();
  void SetData(const std::vector<double> &neurons_values);

  void CalculateValues();

  void UpdateErrorByExpectedIndex(std::size_t expected_index);
  void UpdateErrorByLayer(Layer &layer);
  void UpdateWeights(double learning_rate);

  std::size_t GetMaxValueIndex();

 private:
  std::vector<Neuron> neurons_;
};

#endif  // MLP_LAYER_H_
