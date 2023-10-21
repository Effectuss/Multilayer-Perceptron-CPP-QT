#ifndef GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
#define GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H

#include "dataset.h"
#include "i_activation_function.h"
#include "i_perceptron.h"
#include "layer.h"

class GraphPerceptron final : public IPerceptron {
 public:
  GraphPerceptron(std::size_t hidden_layers_count,
                  std::size_t hidden_layers_size, std::size_t output_layer_size,
                  std::unique_ptr<IActivationFunction>& activationFunction);
  GraphPerceptron() = delete;
  ~GraphPerceptron() override = default;

  std::vector<double> Predict(const Picture& picture) override;

  void Train(std::size_t epochs, const Dataset& dataset) override;
  void Test(double segment, const Dataset& dataset) override;

  void SetActivationFunction(
      std::unique_ptr<IActivationFunction>& activationFunction) override;

  void LoadWeights(const std::string& file_name) override;
  void ExportWeights(const std::string& file_name) override;

 private:
  void Configure(std::size_t input_layer_size);

  void FeedForward(const Picture& picture);
  void PropagateBackwards(std::size_t expected_index);

  static constexpr double learning_rate_ = 0.1;

  std::vector<Layer> layers_;

  std::size_t hidden_layers_count_;
  std::size_t hidden_layers_size_;
  std::size_t output_layer_size_;
  std::shared_ptr<IActivationFunction> activationFunction_;
};

#endif  // GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
