#include <iostream>

#include "graph_perceptron.h"
#include "parser.h"
#include "sigmoid.h"

int main() {
  std::cout << "Parsing train" << std::endl;
  Dataset train_dataset =
      Parser::ParseDataset(R"(D:\Downloads\archive\emnist-letters-train.csv)");
  std::cout << "Parsing test" << std::endl;
  Dataset test_dataset =
      Parser::ParseDataset(R"(D:\Downloads\archive\emnist-letters-test.csv)");

  std::unique_ptr<IActivationFunction> activationFunction =
      std::make_unique<Sigmoid>();

  IPerceptron *perceptron = new GraphPerceptron();
  perceptron->Configure(784, 26, 3, 140);
  perceptron->SetTrainDataset(train_dataset);
  perceptron->SetActivationFunction(activationFunction);
  std::cout << "Training" << std::endl;
  perceptron->Train(1);

  int max = (int)test_dataset.GetDataSize();
  int correct = 0;
  int not1 = 0;
  for (auto &test : test_dataset.GetData()) {
    not1++;
    int result = perceptron->Predict(test.first) + 1;
    if (result == test.second) {
      correct++;
    }
    if (not1 % 1000 == 0) {
      std::cout << "Result [" << not1 << "]: " << 100.0 * correct / max << "%"
                << std::endl;
    }
  }

  std::cout << "Final result: " << 100.0 * correct / max << "%"
            << ". Is this cool?";

  return 0;
}
