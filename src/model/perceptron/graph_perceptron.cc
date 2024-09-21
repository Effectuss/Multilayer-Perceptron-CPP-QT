#include "graph_perceptron.h"

#include <algorithm>

#include "model/perceptron/i_perceptron.h"

GraphPerceptron::GraphPerceptron(
    std::size_t hidden_layers_count, std::size_t hidden_layers_size,
    std::size_t output_layer_size,
    std::shared_ptr<IActivationFunction> activation_function)
    : IPerceptron() {
  SetActivationFunction(activation_function);
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
  for (std::size_t i = 0; !IsCancelled() && i < epochs; ++i) {
    for (auto &item : dataset.GetData()) {
      FeedForward(item.first);
      PropagateBackwards(item.second);
    }
  }

  if (!IsCancelled()) {
    Finish();
  }
}

void GraphPerceptron::SetActivationFunction(
    std::shared_ptr<IActivationFunction> activationFunction) {
  activation_function_ = std::move(activationFunction);
  Neuron::SetActivationFunction(activation_function_);
}

void GraphPerceptron::LoadWeights(const std::string &file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file for reading graph weights");
  }

  std::string header;
  file >> header;
  if (header != "G") {
    file.close();
    throw std::ios_base::failure("Invalid file format for graph weights.");
  }

  *this = GraphPerceptron(file, activation_function_);
}

void GraphPerceptron::ExportWeights(const std::string &file_name) {
  std::ofstream file(file_name);

  if (!file.is_open()) {
    throw std::ios_base::failure(
        "Cannot create or open for write file for weights");
  }

  file << "G" << std::endl;
  file << layers_[0].GetLayerSize() << " ";
  file << hidden_layers_size_ << " ";
  file << hidden_layers_count_ << " ";
  file << output_layer_size_ << " ";

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    file << std::endl;
    for (auto &neuron : layers_[i].GetRawNeuronsData()) {
      for (auto &weight : neuron.GetNeuronWeights()) {
        file << weight << " ";
      }
    }
  }
}

GraphPerceptron &GraphPerceptron::operator=(GraphPerceptron &&other) noexcept {
  if (this != &other) {
    layers_ = std::move(other.layers_);
    hidden_layers_count_ = other.hidden_layers_count_;
    hidden_layers_size_ = other.hidden_layers_size_;
    output_layer_size_ = other.output_layer_size_;
    activation_function_ = std::move(other.activation_function_);
  }

  return *this;
}

GraphPerceptron::GraphPerceptron(
    std::ifstream &weights,
    std::shared_ptr<IActivationFunction> activation_function)
    : IPerceptron() {
  SetActivationFunction(activation_function);
  std::size_t input_layer_size;
  weights >> input_layer_size;
  weights >> hidden_layers_size_;
  weights >> hidden_layers_count_;
  weights >> output_layer_size_;
  Configure(input_layer_size);
  Neuron::SetActivationFunction(activation_function_);

  for (std::size_t i = 1; i < layers_.size(); ++i) {
    for (auto &neuron : layers_[i].GetRawNeuronsData()) {
      std::vector<double> temp_weights;
      for (std::size_t j = 0; j < layers_[i - 1].GetLayerSize(); ++j) {
        double temp_weight;
        weights >> temp_weight;
        if (weights.fail()) {
          weights.close();
          throw std::ios_base::failure("Error in weights file!");
        }
        temp_weights.push_back(temp_weight);
      }
      neuron.SetNeuronsWeights(temp_weights);
    }
  }
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

  for (std::size_t i = 1; !IsCancelled() && i < layers_.size(); ++i) {
    layers_[i].CalculateValues();
  }
}

void GraphPerceptron::PropagateBackwards(std::size_t expected_index) {
  layers_.back().UpdateErrorByExpectedIndex(expected_index);

  for (std::size_t i = layers_.size() - 1; !IsCancelled() && i > 0; --i) {
    layers_[i - 1].UpdateErrorByLayer(layers_[i]);
  }

  for (std::size_t i = 1; !IsCancelled() && i < layers_.size(); ++i) {
    layers_[i].UpdateWeights(learning_rate_);
  }
}
