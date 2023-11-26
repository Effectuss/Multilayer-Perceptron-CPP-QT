#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H

#include "i_perceptron.h"
#include "matrix.h"
#include <iomanip>
#include "mapping.h"

class MatrixPerceptron : public IPerceptron {
public:
    MatrixPerceptron() = delete;
    MatrixPerceptron(int hidden_layers_count,
                     int size_hidden_layers,
                     const Mapping &mapping,
                     std::unique_ptr<IActivationFunction> &activationFunction);

    std::vector<double> Predict(const Picture &picture) override;

    void Train(std::size_t epochs, const Dataset& dataset) override;

    void Test(double segment, const Dataset& dataset) override;

    void SetActivationFunction(
            std::unique_ptr<IActivationFunction> &function) override;

    void LoadWeights(const std::string &file_path) override;

    void ExportWeights(const std::string &file_path) override;

    double TestMatrixPerceptron(const Dataset &test_dataset);

private:
    static constexpr int kMinAmountOfHiddenLayers{2};
    static constexpr int kMaxAmountOfHiddenLayers{5};
    static constexpr double kLearningRate{0.13};

    static bool IsValidDataForPerceptron(int, int);

    void InitRandomWeights();

    void InitNeuronNetwork();

    void InitSizeLayers(int, const Mapping&);

    void InitPerceptronFromFile(const std::string &);

    void SetInputLayer(const Picture &picture);

    std::size_t ForwardFeed();

    static std::size_t FindMaxIndex(const std::vector<double> &vector);

    void BackPropagation(std::size_t expect_index);

    static double CalculateOutputLayerError(double neuron_value, double target);

    double CalculateOutputLayerError(std::size_t neuron_index,
                                     std::size_t expect_index);

    void UpdateWeights(std::size_t layer_in, std::size_t neuron_in,
                       double delta_weight);

    std::size_t number_of_layers_{2};

    std::unique_ptr<IActivationFunction> activation_function_;

    std::vector<std::size_t> size_layers_;
    std::vector<std::vector<double>> neuron_values_;
    std::vector<std::vector<double>> neuron_errors_;
    std::vector<std::vector<double>> delta_weight_;
    std::vector<Matrix> weights_;
};

#endif // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_PERCEPTRON_H
