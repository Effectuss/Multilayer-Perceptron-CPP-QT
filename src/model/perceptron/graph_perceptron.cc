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
                     .ConnectPrevious(last_layer)
                     .GenerateWeights();
  }
  layers_.emplace_back(output_layer_size)
      .ConnectPrevious(last_layer)
      .GenerateWeights();
}

void GraphPerceptron::SetTrainDataset(Dataset &dataset) {
  train_dataset_ = dataset;
}

void GraphPerceptron::SetTestDataset(Dataset &dataset) {
  test_dataset_ = dataset;
}

void GraphPerceptron::SetActivationFunction(
    std::unique_ptr<IActivationFunction> &activationFunction) {
  activationFunction_ = std::move(activationFunction);
  Neuron::SetActivationFunction(activationFunction_);
}

int GraphPerceptron::Predict(Picture &picture) {
  FeedForward(picture);
  return 0;
}

void GraphPerceptron::Train(std::size_t epochs) {
  for (std::size_t i = 0; i < epochs; ++i) {
    for (auto &item : train_dataset_.GetData()) {
      FeedForward(item.first);
      PropagateBackwards(item.second);
    }
  }
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

void GraphPerceptron::FeedForward(const Picture &picture) {
  layers_.front().SetData(picture.GetData());

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    layers_[i].CalculateValues();
  }
}

void GraphPerceptron::PropagateBackwards(std::size_t expected_index) {
  expected_index -= starting_index;

  layers_.back().UpdateErrorByExpectedIndex(expected_index);

  for (std::size_t i = layers_.size() - 2; i > 0; --i) {
    layers_[i].UpdateErrorByLayer(layers_[i + 1]);
  }

  for (std::size_t i = 1; i < layers_.size() - 1; ++i) {
    layers_[i].UpdateWeightsByLayer(layers_[i - 1]);
  }
}
