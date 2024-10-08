#include "neuron.h"

#include <algorithm>
#include <random>

std::shared_ptr<IActivationFunction> Neuron::activation_function_;

Neuron::Neuron()
    : value_(0),
      error_(0),
      weights_delta_(0),
      previous_neurons_weights_(0),
      previous_neurons_(0) {}

Neuron::Neuron(double value) : Neuron() { value_ = value; }

void Neuron::SetActivationFunction(
    std::shared_ptr<IActivationFunction>& activationFunction) {
  activation_function_ = activationFunction;
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
  value_ = activation_function_->Activate(value_);
}

double Neuron::GetValue() const { return value_; }

void Neuron::SetValue(double value) { value_ = value; }

void Neuron::SetError(double error) { error_ = error; }

void Neuron::CalculateWeightsDelta() {
  weights_delta_ = error_ * activation_function_->Derivative(value_);
}

double Neuron::GetWeightsDelta() const { return weights_delta_; }

void Neuron::UpdateWeights(double learning_rate) {
  for (std::size_t i = 0; i < previous_neurons_weights_.size(); ++i) {
    previous_neurons_weights_[i] -=
        previous_neurons_[i]->value_ * GetWeightsDelta() * learning_rate;
  }
}

std::vector<double>& Neuron::GetNeuronWeights() {
  return previous_neurons_weights_;
}

void Neuron::SetNeuronsWeights(std::vector<double>& weights) {
  for (std::size_t i = 0; i < previous_neurons_weights_.size(); ++i) {
    previous_neurons_weights_[i] = weights[i];
  }
}
