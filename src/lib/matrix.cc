#include "matrix.h"

Matrix::Matrix(const int& rows, const int& cols)
    : rows_(rows),
      cols_(cols),
      matrix_{std::vector(rows, std::vector<double>(cols))} {}

int Matrix::GetRows() const { return rows_; }
int Matrix::GetCols() const { return cols_; }

double& Matrix::operator()(std::size_t index_i, std::size_t index_j) {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}
const double& Matrix::operator()(std::size_t index_i,
                                 std::size_t index_j) const {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}

std::vector<double> Matrix::MultiplyMatrixByVector(
    const std::vector<double>& vec) const {
  if (cols_ != vec.size()) {
    throw std::runtime_error(
        "The amount of cols in matrix have to equal size vector!");
  }
  std::vector<double> result_vec;
  return result_vec;
}