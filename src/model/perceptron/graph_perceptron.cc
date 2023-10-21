#include "graph_perceptron.h"

#include <algorithm>

GraphPerceptron::GraphPerceptron(
    std::size_t hidden_layers_count, std::size_t hidden_layers_size,
    std::size_t output_layer_size,
    std::unique_ptr<IActivationFunction> &activationFunction) {
  SetActivationFunction(activationFunction);
  hidden_layers_count_ = hidden_layers_count;
  hidden_layers_size_ = hidden_layers_size;
  output_layer_size_ = output_layer_size;
}

std::vector<double> GraphPerceptron::Predict(const Picture &picture) {
  FeedForward(picture);
  return layers_.back().GetNeuronsData();
}

void GraphPerceptron::Train(std::size_t epochs, const Dataset &dataset) {
  Configure(dataset.GetData()[0].first.GetSize());
  for (std::size_t i = 0; i < epochs; ++i) {
    for (auto &item : dataset.GetData()) {
      FeedForward(item.first);
      PropagateBackwards(item.second);
    }
  }
}

void GraphPerceptron::Test(double segment, const Dataset &dataset) {
  // todo
}

void GraphPerceptron::SetActivationFunction(
    std::unique_ptr<IActivationFunction> &activationFunction) {
  activationFunction_ = std::move(activationFunction);
  Neuron::SetActivationFunction(activationFunction_);
}

void GraphPerceptron::LoadWeights(const std::string &file_name) {
  // todo
}

void GraphPerceptron::ExportWeights(const std::string &file_name) {
  // todo
}

void GraphPerceptron::Configure(std::size_t input_layer_size) {
  layers_.emplace_back(input_layer_size);
  for (std::size_t i = 0; i < hidden_layers_count_; ++i) {
    layers_.push_back(Layer(hidden_layers_size_)
                          .ConnectPrevious(layers_.back())
                          .GenerateWeights());
  }
  layers_.push_back(Layer(output_layer_size_)
                        .ConnectPrevious(layers_.back())
                        .GenerateWeights());
}

void GraphPerceptron::FeedForward(const Picture &picture) {
  layers_.front().SetNeuronsData(picture.GetData());

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    layers_[i].CalculateValues();
  }
}

void GraphPerceptron::PropagateBackwards(std::size_t expected_index) {
  layers_.back().UpdateErrorByExpectedIndex(expected_index);

  for (std::size_t i = layers_.size() - 1; i > 0; --i) {
    layers_[i - 1].UpdateErrorByLayer(layers_[i]);
  }

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    layers_[i].UpdateWeights(learning_rate_);
  }
}
