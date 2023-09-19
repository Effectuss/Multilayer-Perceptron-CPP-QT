#ifndef GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
#define GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H

#include "dataset.h"
#include "i_activation_function.h"
#include "i_perceptron.h"

class GraphPerceptron final : public IPerceptron {
 public:
  GraphPerceptron();
  ~GraphPerceptron() override;

  void Configure(std::size_t input_layer_size, std::size_t output_layer_size,
                 std::size_t hidden_layers_count,
                 std::size_t hidden_layers_size) override;

  void SetTrainDataset(Dataset &dataset) override;
  void SetTestDataset(Dataset &dataset) override;
  void SetActivationFunction(
      std::unique_ptr<IActivationFunction> &activationFunction) override;

  int Predict(Picture &picture) override;
  void Train(std::size_t epochs) override;
  void CrossValidation(std::size_t groups) override;

  void LoadWeights(const std::istream &istream) override;
  void ExportWeights(const std::ostream &ostream) override;

 private:
  class Layer final {
   private:
    class Neuron;

   public:
    Layer() = delete;
    explicit Layer(int neuron_amount);

    Layer &ConnectLayer(Layer &previous);
    Layer &GenerateWeights();
    void SetPicture(const Picture &picture);

    std::vector<Neuron>::iterator begin();
    std::vector<Neuron>::iterator end();

   private:
    class Neuron final {
     public:
      void SetValue(double value);
      double CalculateValue();

      void ConnectNeurons(std::vector<Neuron> &neurons);
      void GenerateWeights();

     private:
      double value_ = 0;
      double error_ = 0;
      double weights_delta_ = 0;
      std::vector<double> previous_neurons_weights_;
      std::vector<Neuron *> previous_neurons_;
    };

    std::vector<Neuron> neurons_;
  };

  void FeedForward(const Picture &picture);
  void PropagateBackwards(std::size_t expected_index);

  std::vector<Layer> layers_;

  Dataset train_dataset_;
  Dataset test_dataset_;
  std::unique_ptr<IActivationFunction> activationFunction_;
};

#endif  // GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
