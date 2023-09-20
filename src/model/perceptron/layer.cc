#include "layer.h"

Layer::Layer(int number_of_neurons) { neurons_.resize(number_of_neurons); }

Layer& Layer::ConnectPrevious(const Layer& other) {
  for (auto& neuron : neurons_) {
    neuron.ConnectNeurons(other.neurons_);
  }

  return *this;
}

Layer& Layer::GenerateWeights() {
  for (auto& neuron : neurons_) {
    neuron.GenerateWeights();
  }

  return *this;
}

void Layer::SetData(const std::vector<double>& neurons_data) {
  for (std::size_t i = 0; i < neurons_data.size(); ++i) {
    neurons_[i] = Neuron(neurons_data[i]);
  }
}

void Layer::CalculateValues() {
  for(auto &neuron : neurons_) {
    neuron.CalculateValue();
  }
}
