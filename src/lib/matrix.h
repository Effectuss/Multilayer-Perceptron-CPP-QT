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

  [[nodiscard]] std::size_t GetRows() const;

  [[nodiscard]] std::size_t GetCols() const;

  double &operator()(std::size_t index_i, std::size_t index_j);

  const double &operator()(std::size_t index_i, std::size_t index_j) const;

  void FillMatrixRandomValues(double min_random_value = -1.0,
                              double max_random_value = 1.0);

  static void MultiplyByVector(const Matrix &matrix,
                               const std::vector<double> &vector_column,
                               std::vector<double> &vector_res);

  [[nodiscard]] const std::vector<double>& GetVectorByRows(std::size_t row) const;

private:
  static bool IsCorrectIndex(int, int);

  std::size_t rows_{};
  std::size_t cols_{};
  std::vector<std::vector<double>> matrix_;

  static std::random_device rd_;
  static std::mt19937 gen_;
};

#endif // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_H
