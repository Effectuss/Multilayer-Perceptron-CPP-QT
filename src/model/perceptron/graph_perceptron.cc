#include "graph_perceptron.h"

#include <algorithm>
#include <random>

GraphPerceptron::GraphPerceptron() = default;

GraphPerceptron::~GraphPerceptron() = default;

void GraphPerceptron::Configure(std::size_t input_layer_size,
                                std::size_t output_layer_size,
                                std::size_t hidden_layers_count,
                                std::size_t hidden_layers_size) {
  layers_.clear();
  Layer last_layer = layers_.emplace_back(input_layer_size);
  for (std::size_t i = 0; i < hidden_layers_count; ++i) {
    last_layer = layers_.emplace_back(hidden_layers_size)
                     .ConnectLayer(last_layer)
                     .GenerateWeights();
  }
  layers_.emplace_back(output_layer_size)
      .ConnectLayer(last_layer)
      .GenerateWeights();
}

void GraphPerceptron::SetTrainDataset(Dataset &dataset) {
  train_dataset_ = dataset;
}

void GraphPerceptron::SetTestDataset(Dataset &dataset) {
  test_dataset_ = dataset;
}

void GraphPerceptron::SetActivationFunction(
    IActivationFunction *activationFunction) {
  activationFunction_ = activationFunction;
}

int GraphPerceptron::Predict(Picture &picture) {
  layers_.front().SetPicture(picture);
  FeedForward();
  // todo: return max value from last layer
  return 0;
}

void GraphPerceptron::Train(std::size_t epochs) {
  // todo
}

void GraphPerceptron::CrossValidation(std::size_t groups) {
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

void GraphPerceptron::Layer::SetPicture(Picture &picture) {
  // do I need this check here?
  if (neurons_.size() != picture.GetSize()) {
    throw std::logic_error(
        "Graph perceptron first layer size != picture size!");
  }

  for (std::size_t i = 0; i < neurons_.size(); ++i) {
    neurons_[i].value_ = picture.GetData()[i];
  }
}
