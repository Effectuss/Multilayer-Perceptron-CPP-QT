#ifndef GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
#define GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H

#include "dataset.h"
#include "i_activation_function.h"
#include "i_perceptron.h"
#include "layer.h"

class GraphPerceptron final : public IPerceptron {
 public:
  GraphPerceptron() = default;
  ~GraphPerceptron() override = default;

  void Configure(std::size_t input_layer_size, std::size_t output_layer_size,
                 std::size_t hidden_layers_count,
                 std::size_t hidden_layers_size) override;

  void SetTrainDataset(Dataset &dataset) override;
  void SetTestDataset(Dataset &dataset) override;
  void SetActivationFunction(
      std::unique_ptr<IActivationFunction> &activationFunction) override;

  int Predict(const Picture &picture) override;
  void Train(std::size_t epochs) override;
  void CrossValidation(std::size_t groups) override;

  void LoadWeights(const std::istream &istream) override;
  void ExportWeights(const std::ostream &ostream) override;

 private:
  void FeedForward(const Picture &picture);
  void PropagateBackwards(std::size_t expected_index);

  int starting_index = 1;

  std::vector<Layer> layers_;

  Dataset train_dataset_;
  Dataset test_dataset_;
  std::shared_ptr<IActivationFunction> activationFunction_;
};

#endif  // GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
