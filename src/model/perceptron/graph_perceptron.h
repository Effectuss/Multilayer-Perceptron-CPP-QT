#ifndef GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
#define GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H

#include "dataset.h"
#include "i_activation_function.h"
#include "i_perceptron.h"
#include "mapping.h"

class GraphPerceptron final : IPerceptron {
 public:
  GraphPerceptron() = delete;
  GraphPerceptron(IActivationFunction *activationFunction,
                  const Dataset &dataset, const Mapping &mapping,
                  int hidden_layers_count, int size_hidden_layers);
  ~GraphPerceptron() override = default;

  int Predict(Picture picture) override;
  void Train(int epochs) override;
  void LoadWeights(const std::istream &) override;
  void ExportWeights(const std::ostream &) override;

 private:
  class Layer final {
   public:
    Layer() = delete;
    explicit Layer(int neuron_amount);

    Layer &ConnectLayer(Layer &previous);
    Layer &GenerateWeights();

   private:
    // friend class GraphPerceptron;

    class Neuron final {
     public:
     private:
      friend class Layer;

      double value_ = 0;
      double error_ = 0;
      double weights_delta_ = 0;
      std::vector<double> previous_neurons_weights_;
      std::vector<Neuron *> previous_neurons_;
    };

    std::vector<Neuron> neurons_;
  };

  void FeedForward();
  void PropagateBackwards();

  // do I really need this field?
  // int layer_count_;
  std::vector<Layer> layers_;
};

#endif  // GRAPH_PERCEPTRON_GRAPH_PERCEPTRON_H
