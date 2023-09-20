#include "neuron.h"

#include <random>

Neuron::Neuron()
    : value_(0),
      error_(0),
      weights_delta_(0),
      previous_neurons_weights_(0),
      previous_neurons_(0) {}

Neuron::Neuron(double value) : Neuron() { value_ = value; }

void Neuron::SetActivationFunction(
    std::shared_ptr<IActivationFunction>& activationFunction) {
  activationFunction_ = activationFunction;
}

void Neuron::ConnectNeurons(const std::vector<Neuron>& neurons) {
  previous_neurons_.resize(neurons.size());

  std::transform(neurons.begin(), neurons.end(), previous_neurons_.begin(),
                 [](const Neuron& n) { return &n; });
}

void Neuron::GenerateWeights() {
  std::uniform_real_distribution<double> dist(-0.5, 0.5);
  static std::random_device rd_;
  static std::mt19937 generator_(rd_());

  previous_neurons_weights_.resize(previous_neurons_.size());

  std::transform(previous_neurons_weights_.begin(),
                 previous_neurons_weights_.end(),
                 previous_neurons_weights_.begin(),
                 [&](double) { return dist(generator_); });
}

void Neuron::CalculateValue() {
  value_ = 0;
  for (std::size_t i = 0; i < previous_neurons_.size(); ++i) {
    value_ += previous_neurons_[i]->value_ * previous_neurons_weights_[i];
  }
  value_ = activationFunction_->Activate(value_);
}
