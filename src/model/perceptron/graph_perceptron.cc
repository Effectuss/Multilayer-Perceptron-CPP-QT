#include "graph_perceptron.h"

#include <algorithm>

void GraphPerceptron::Configure(std::size_t input_layer_size,
                                std::size_t output_layer_size,
                                std::size_t hidden_layers_count,
                                std::size_t hidden_layers_size) {
  layers_.clear();
  layers_.emplace_back(input_layer_size);
  for (std::size_t i = 0; i < hidden_layers_count; ++i) {
    layers_.push_back(Layer(hidden_layers_size)
                          .ConnectPrevious(layers_.back())
                          .GenerateWeights());
  }
  layers_.push_back(Layer(output_layer_size)
                        .ConnectPrevious(layers_.back())
                        .GenerateWeights());
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

// todo: maybe fix return type of predict
int GraphPerceptron::Predict(const Picture &picture) {
  FeedForward(picture);
  return (int)layers_.back().GetMaxValueIndex();
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
  expected_index -= starting_index_;

  layers_.back().UpdateErrorByExpectedIndex(expected_index);

  for (std::size_t i = layers_.size() - 2; i > 0; --i) {
    layers_[i - 1].UpdateErrorByLayer(layers_[i]);
  }

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    layers_[i].UpdateWeightsByLayer(layers_[i - 1], learning_rate_);
  }
}
