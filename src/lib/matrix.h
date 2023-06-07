#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>

class Matrix {
 public:
  Matrix() = default;
  Matrix(const int& rows, const int& cols);
  Matrix(const Matrix& over_matri) = default;
  Matrix(Matrix&& over_matrix) = default;
  Matrix& operator=(const Matrix& ower_matirx) = default;
  Matrix& operator=(Matrix&& over_matrix) = default;
  ~Matrix() = default;

  int GetRows() const;
  int GetCols() const;

  double& operator()(int index_i, int index_j);
  const double& operator()(int index_i, int index_j) const;

  std::vector<double> MultiplyMatrixByVector(
      const std::vector<double>& vec) const;
  void FillMatrixRandomValues(double min_random_value = 0.1,
                              double max_random_value = 0.5);

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<double>> matrix_;

  static std::random_device rd_;
  static std::mt19937 gen_;
};

#endif  // __MATRIX_H__