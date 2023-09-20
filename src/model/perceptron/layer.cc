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
  for (auto& neuron : neurons_) {
    neuron.CalculateValue();
  }
}

void Layer::UpdateErrorByExpectedIndex(std::size_t expected_index) {
  for (std::size_t i = 0; i < neurons_.size(); ++i) {
    if (i == expected_index) {
      neurons_[i].SetError(neurons_[i].GetValue() - 1.0);
    } else {
      neurons_[i].SetError(neurons_[i].GetValue());
    }
  }
}

void Layer::UpdateErrorByLayer(const Layer& layer) {
  for (auto& neuron : neurons_) {
    double error = 0;
    auto weights = neuron.GetNeuronWeights();
    for (std::size_t i = 0; i < layer.neurons_.size(); ++i) {
      error += weights[i] * layer.neurons_[i].GetError();
    }
    neuron.SetError(error);
    neuron.CalculateWeightsDelta();
  }
}

// todo: extract somewhere learning rate
// layer = prev layer
void Layer::UpdateWeightsByLayer(Layer& layer) {
  double learning_rate = 0.1;

  for (std::size_t i = 0; i < neurons_.size(); ++i) {
    //
  }

  // weights[i] = weights[i] - layer.neuron_[i].value * delta[i] * learning_rate
}