#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_H

#include <algorithm>
#include <istream>
#include <ostream>
#include <random>
#include <stdexcept>
#include <vector>

class Matrix {
 public:
  Matrix() = default;

  Matrix(int rows, int cols);

  Matrix(const Matrix &other_matrix) = default;

  Matrix(Matrix &&over_matrix) = default;

  Matrix &operator=(const Matrix &other_matrix) = default;

  Matrix &operator=(Matrix &&other_matrix) = default;

  [[nodiscard]] int GetRows() const;

  [[nodiscard]] int GetCols() const;

  double &operator()(int index_i, int index_j);

  const double &operator()(int index_i, int index_j) const;

  void FillMatrixRandomValues(double min_random_value = -1.0,
                              double max_random_value = 1.0);

 private:
  static bool IsCorrectIndex(int, int);

  int rows_{};
  int cols_{};
  std::vector<std::vector<double>> matrix_;

  static std::random_device rd_;
  static std::mt19937 gen_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_H
