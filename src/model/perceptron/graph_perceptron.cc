#include "graph_perceptron.h"

#include <algorithm>
#include <random>

GraphPerceptron::GraphPerceptron(IActivationFunction *activationFunction,
                                 const Dataset &dataset, const Mapping &mapping,
                                 int hidden_layers_count,
                                 int size_hidden_layers) {
  //  layer_count_ = 2 + hidden_layers_count;
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

void GraphPerceptron::Layer::ConnectLayer(Layer &previous) {
  for (auto &neuron : neurons_) {
    neuron.previous_neurons_.resize(previous.neurons_.size());
    std::transform(previous.neurons_.begin(), previous.neurons_.end(),
                   neuron.previous_neurons_.begin(),
                   [](Neuron &n) { return &n; });
  }
}

// todo: "true" randomness
void GraphPerceptron::Layer::GenerateWeights() {
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
}
