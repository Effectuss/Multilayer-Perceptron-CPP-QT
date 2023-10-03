#include "matrix_perceptron.h"

#include <chrono>
#include <fstream>
#include <sstream>

bool MatrixPerceptron::IsValidDataForPerceptron(int hidden_layers_count,
                                                int size_hidden_layers) {
  return (hidden_layers_count <= kMaxAmountOfHiddenLayers &&
          hidden_layers_count >= kMinAmountOfHiddenLayers) &&
         size_hidden_layers > 0;
}

MatrixPerceptron::MatrixPerceptron(int hidden_layers_count,
                                   int size_hidden_layers) {
  if (!IsValidDataForPerceptron(hidden_layers_count, size_hidden_layers)) {
    throw std::invalid_argument("Incorrect data for perceptron!");
  }

  number_of_layers_ = hidden_layers_count + 2;

  InitSizeLayers(size_hidden_layers);
  InitRandomWeights();
  InitNeuronNetwork();
}

void MatrixPerceptron::InitSizeLayers(int size_hidden) {
  for (int i = 0; i < number_of_layers_; ++i) {
    if (i == 0) {
      // todo magic number
      size_layers_.push_back(784);
    } else if (i == number_of_layers_ - 1) {
      // todo magic number
      size_layers_.push_back(26);
    } else {
      size_layers_.push_back(size_hidden);
    }
  }
}

void MatrixPerceptron::InitRandomWeights() {
  weights_.resize(number_of_layers_);

  for (int i = 1; i < number_of_layers_; ++i) {
    weights_[i] = std::move(Matrix(size_layers_[i], size_layers_[i - 1]));
    weights_[i].FillMatrixRandomValues();
  }
}

void MatrixPerceptron::InitNeuronNetwork() {
  for (int i = 0; i < number_of_layers_; ++i) {
    neuron_values_.emplace_back(size_layers_[i]);
    neuron_errors_.emplace_back(size_layers_[i]);
    delta_weight_.emplace_back(size_layers_[i]);
  }
}

void MatrixPerceptron::SetActivationFunction(
    std::unique_ptr<IActivationFunction> &function) {
  activation_function_ = std::move(function);
}

void MatrixPerceptron::SetTrainDataset(Dataset &dataset) { dataset_ = dataset; }

std::size_t MatrixPerceptron::ForwardFeed() {
  for (int i = 1; i < number_of_layers_; ++i) {
    Matrix::MultiplyByVector(weights_[i], neuron_values_[i - 1],
                             neuron_values_[i]);
    activation_function_->Activate(neuron_values_[i]);
  }
  return FindMaxIndex(neuron_values_[number_of_layers_ - 1]);
}

std::size_t MatrixPerceptron::FindMaxIndex(const std::vector<double> &vector) {
  if (vector.empty())
    return 0;

  std::size_t max_index = 0;
  for (std::size_t i = 0; i < vector.size(); ++i) {
    if (vector[i] >= vector[max_index]) {
      max_index = i;
    }
  }
  return max_index;
}

void MatrixPerceptron::SetInputLayer(const Picture &picture) {
  if (picture.GetSize() != neuron_values_[0].size()) {
    throw std::runtime_error("Invalid picture for input layer!");
  }

  neuron_values_[0] = picture.GetData();
}

void MatrixPerceptron::Train(int epochs) {
  while (epochs--) {
    // todo delete time
    auto start = std::chrono::high_resolution_clock::now();
    int ra = 0;
    double curr_lr = kLearningRate * std::exp(-kDecayRate * epoch_);
    std::cout << curr_lr << std::endl;
    int dataset_size = static_cast<int>(dataset_.GetDataSize());
    for (int i = 0; i < dataset_size; ++i) {
      SetInputLayer(dataset_.GetData()[i].first);
      std::size_t max_index = ForwardFeed();
      int expect_value = dataset_.GetData()[i].second - 1;
      BackPropagation(expect_value);
      if (max_index == expect_value) {
        ++ra;
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "After one epoch: "
              << (double)ra / (double)dataset_.GetDataSize() * 100.0
              << std::endl;
    std::cout << "Time execute one epoch: " << duration.count() << " sec"
              << std::endl;
    // todo delete
    ++epoch_;
  }
}

void MatrixPerceptron::BackPropagation(std::size_t expect_index) {
  for (std::size_t layer_in = number_of_layers_ - 1; layer_in != 0;
       --layer_in) {
    for (std::size_t neuron_in = 0; neuron_in < neuron_errors_[layer_in].size();
         ++neuron_in) {
      double error = 0.0;
      if (layer_in == number_of_layers_ - 1) {
        error = CalculateOutputLayerError(neuron_in, expect_index);
      } else {
        for (std::size_t neuron_right = 0;
             neuron_right < delta_weight_[layer_in + 1].size();
             ++neuron_right) {
          error += delta_weight_[layer_in + 1][neuron_right] *
                   weights_[layer_in + 1](neuron_right, neuron_in);
        }
      }

      neuron_errors_[layer_in][neuron_in] = error;

      double delta_weight = error * activation_function_->Derivative(
                                        neuron_values_[layer_in][neuron_in]);
      delta_weight_[layer_in][neuron_in] = delta_weight;
      UpdateWeights(layer_in, neuron_in, delta_weight);
    }
  }
}

double MatrixPerceptron::CalculateOutputLayerError(double neuron_value,
                                                   double target) {
  return neuron_value - target;
}

double MatrixPerceptron::CalculateOutputLayerError(std::size_t neuron_in,
                                                   std::size_t expect_in) {
  if (expect_in == neuron_in) {
    return CalculateOutputLayerError(
        neuron_values_[number_of_layers_ - 1][neuron_in], 1.0);
  } else {
    return CalculateOutputLayerError(
        neuron_values_[number_of_layers_ - 1][neuron_in], 0.0);
  }
}

void MatrixPerceptron::UpdateWeights(std::size_t layer_in,
                                     std::size_t neuron_in,
                                     double delta_weight) {
  for (std::size_t weight_in = 0;
       weight_in < weights_[layer_in].GetVectorByRows(neuron_in).size();
       ++weight_in) {
    weights_[layer_in](neuron_in, weight_in) =
        weights_[layer_in](neuron_in, weight_in) -
        neuron_values_[layer_in - 1][weight_in] * delta_weight * kLearningRate;
  }
}

double MatrixPerceptron::TestMatrixPerceptron(const Dataset &test_dataset) {
  int right_answer = 0;
  for (std::size_t i = 0; i < test_dataset.GetDataSize(); ++i) {
    SetInputLayer(test_dataset.GetData()[i].first);
    std::size_t max_index = ForwardFeed();
    if (max_index == test_dataset.GetData()[i].second - 1) {
      ++right_answer;
    }
  }

  return (double)right_answer / (double)test_dataset.GetDataSize() * 100.0;
}

void MatrixPerceptron::ExportWeights(const std::string &file_path) {
  std::ofstream file_out;
  file_out.open(file_path);

  if (!file_out.is_open()) {
    throw std::runtime_error("Can't write to file");
  }

  file_out << "M"
           << "\n";

  for (int size_layer : size_layers_) {
    file_out << size_layer << " ";
  }

  file_out << "\n";

  for (int i = 1; i < number_of_layers_; ++i) {
    file_out << weights_[i];
  }
  file_out.close();
}

void MatrixPerceptron::LoadWeights(const std::string &file_path) {
  std::ifstream file_in;
  file_in.open(file_path);

  if (!file_in.is_open()) {
    throw std::runtime_error("Can't read from file");
  }
  std::string check_type;
  std::getline(file_in, check_type);
  if (check_type != "M") {
    throw std::logic_error(
        "The file with matrix weight should be start with 'M'!");
  }

  std::string settings;
  std::getline(file_in, settings);

  InitPerceptronFromFile(settings);

  for (int i = 1; i < number_of_layers_; ++i) {
    file_in >> weights_[i];
  }

  file_in.close();
}

void MatrixPerceptron::InitPerceptronFromFile(const std::string &settings) {
  std::istringstream iss(settings);

  size_layers_.clear();
  neuron_values_.clear();
  neuron_errors_.clear();
  delta_weight_.clear();
  weights_.clear();

  std::vector<int> numbers;

  int number;

  while (iss >> number) {
    numbers.push_back(number);
  }

  size_layers_ = numbers;
  number_of_layers_ = size_layers_.size();

  InitRandomWeights();
  InitNeuronNetwork();

}
