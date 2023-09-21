#ifndef MLP_NEURON_H_
#define MLP_NEURON_H_

#include <memory>
#include <vector>

#include "i_activation_function.h"

class Neuron final {
 public:
  Neuron();
  explicit Neuron(double value);
  Neuron(const Neuron &other) = default;
  Neuron(Neuron &&other) = default;
  Neuron &operator=(const Neuron &other) = default;
  Neuron &operator=(Neuron &&other) = default;
  ~Neuron() = default;

  static void SetActivationFunction(
      std::shared_ptr<IActivationFunction> &activationFunction);

  void ConnectNeurons(const std::vector<Neuron> &neurons);
  void GenerateWeights();

  void CalculateValue();

  double GetValue() const;

  double GetError() const;
  void SetError(double error);

  void CalculateWeightsDelta();

  std::vector<double> &GetNeuronWeights();

 private:
  static std::shared_ptr<IActivationFunction> activationFunction_;

  double value_;
  double error_;
  double weights_delta_;
  std::vector<double> previous_neurons_weights_;
  std::vector<const Neuron *> previous_neurons_;
};

#endif  // MLP_NEURON_H_
