#include "graph_perceptron.h"

#include <algorithm>
#include <random>

GraphPerceptron::GraphPerceptron(IActivationFunction *activationFunction,
                                 const Dataset &dataset, const Mapping &mapping,
                                 int hidden_layers_count,
                                 int size_hidden_layers) {
  // todo: remove magic number
  int magic_number1 = 784;
  Layer &last_layer = layers_.emplace_back(magic_number1);
  for (std::size_t i = 0; i < hidden_layers_count; ++i) {
    last_layer = layers_.emplace_back(size_hidden_layers)
                     .ConnectLayer(last_layer)
                     .GenerateWeights();
  }
  // todo: remove magic number
  // I know I can get it from mapping, but I wanna get rid of it
  int magic_number2 = 26;
  layers_.emplace_back(magic_number2)
      .ConnectLayer(last_layer)
      .GenerateWeights();
}

int GraphPerceptron::Predict(Picture picture) {
  // todo
  return 0;
}

void GraphPerceptron::Train(int epochs) {
  // todo
}

void GraphPerceptron::LoadWeights(const std::istream &) {
  // todo
}

void GraphPerceptron::ExportWeights(const std::ostream &) {
  // todo
}

void GraphPerceptron::FeedForward() {
  // todo
}

void GraphPerceptron::PropagateBackwards() {
  // todo
}

GraphPerceptron::Layer::Layer(int neuron_amount) {
  neurons_.resize(neuron_amount);
}

GraphPerceptron::Layer &GraphPerceptron::Layer::ConnectLayer(Layer &previous) {
  for (auto &neuron : neurons_) {
    neuron.previous_neurons_.resize(previous.neurons_.size());
    std::transform(previous.neurons_.begin(), previous.neurons_.end(),
                   neuron.previous_neurons_.begin(),
                   [](Neuron &n) { return &n; });
  }

  return *this;
}

// todo: "true" randomness
GraphPerceptron::Layer &GraphPerceptron::Layer::GenerateWeights() {
  double lower = -0.5;
  double upper = 0.5;

  std::uniform_real_distribution<double> dist(lower, upper);
  static std::random_device rd_;
  static std::mt19937 generator_;

  for (auto &neuron : neurons_) {
    neuron.previous_neurons_weights_.resize(neuron.previous_neurons_.size());
    std::transform(neuron.previous_neurons_weights_.begin(),
                   neuron.previous_neurons_weights_.end(),
                   neuron.previous_neurons_weights_.begin(),
                   [](double) { return 5; });
  }

  return *this;
}
