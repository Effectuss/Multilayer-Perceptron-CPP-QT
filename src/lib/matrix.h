#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>

class Matrix {
 public:
  Matrix() = delete;
  Matrix(const int& rows, const int& cols);
  Matrix(const Matrix& over_matri) = default;
  Matrix(Matrix&& over_matrix) = default;
  Matrix& operator=(const Matrix& ower_matirx) = default;
  Matrix& operator=(Matrix&& over_matrix) = default;
  ~Matrix() = default;

  int GetRows() const;
  int GetCols() const;

  double& operator()(std::size_t index_i, std::size_t index_j);
  const double& operator()(std::size_t index_i, std::size_t index_j) const;

  std::vector<double> MultiplyMatrixByVector(
      const std::vector<double>& vec) const;

 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<std::vector<double>> matrix_;
};

#endif  // __MATRIX_H__