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

  ~Matrix() = default;

  [[nodiscard]] int GetRows() const;

  [[nodiscard]] int GetCols() const;

  double &operator()(int index_i, int index_j);

  const double &operator()(int index_i, int index_j) const;

  [[nodiscard]] Matrix MultiplyByMatrix(const Matrix &other_matrix) const;

  [[nodiscard]] std::vector<double> MultiplyByVector(
      const std::vector<double> &) const;

  void FillMatrixRandomValues(double min_random_value = 0.1,
                              double max_random_value = 0.5);

  Matrix operator*(const Matrix &) const;

  std::vector<double> operator*(const std::vector<double> &) const;

  friend std::ostream &operator<<(std::ostream &, const Matrix &);

  friend std::istream &operator>>(std::istream &, Matrix &);

  std::vector<double> &operator[](int);

  const std::vector<double> &operator[](int rows) const;

 private:
  static bool IsCorrectIndex(int, int);

  int rows_{};
  int cols_{};
  std::vector<std::vector<double>> matrix_;

  static std::random_device rd_;
  static std::mt19937 gen_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MATRIX_H
