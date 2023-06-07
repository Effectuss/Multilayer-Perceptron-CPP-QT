#ifndef __MATRIX_PERCEPTRON_H__
#define __MATRIX_PERCEPTRON_H__

#include <memory>

#include "../lib/matrix.h"
#include "./activation_function/sigmoid.h"
#include "perceptron_interface.h"

class MatrixPerceptron : public PerceptronInterface {
 public:
  // от 2 до 5, количество слоев всего + 2, in out
  MatrixPerceptron(int hidden_layers_count, int size_hidden_layers);
  // можно добавить конструктор который сразу принимает файл с весами
  // можно добавить конструктор который позволяет создать сеть с разным
  // количеством нейронов на скрытых слоях

  // ?
  void SetDataset();
  void Train();
  void PredictResult();

 private:
  void InitSizeLayers(int size_hidden);
  void InitRandomWeights();
  void InitMatricesNeurons();

  int number_of_layers_{2};
  std::unique_ptr<ActivationFunctionInterface> activation_function_;
  std::vector<int> size_layers_;
  std::vector<Matrix> weights_;
  std::vector<Matrix> neuron_values_;
  std::vector<Matrix> neuron_errors_;
  bool dataset_download_{false};
};

#endif  // __MATRIX_PERCEPTRON_H__