#include <iostream>

#include "matrix_perceptron.h"
#include "parser.h"
#include "sigmoid.h"

int main() {
    std::unique_ptr<IActivationFunction> sigmoid = std::make_unique<Sigmoid>();

    Dataset dataset = Parser::ParseDataset(
            "/Users/englishk/goinfre/emnist-letters/emnist-letters-train.csv");
    Dataset test_dataset = Parser::ParseDataset(
            "/Users/englishk/goinfre/emnist-letters/emnist-letters-test.csv");

    Mapping mapping = Parser::ParseMapping(
            "/Users/englishk/goinfre/emnist-letters/emnist-letters-mapping.txt"
    );

    MatrixPerceptron perceptron(3, 144, mapping, sigmoid);

    perceptron.LoadWeights("/Users/englishk/goinfre/weight.txt");

//    for (int i = 0; i < 3; ++i) {
//        perceptron.Train(1, dataset);
        double r_p = perceptron.TestMatrixPerceptron(test_dataset);
        std::cout << "AFTER TEST: " << r_p << "%" << std::endl;
//    }


//    perceptron.ExportWeights("/Users/englishk/goinfre/weight.txt");

    return 1;
}
