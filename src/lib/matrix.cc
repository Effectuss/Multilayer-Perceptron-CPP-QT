#include "matrix.h"

std::random_device Matrix::rd_;

std::mt19937 Matrix::gen_(rd_());

Matrix::Matrix(const int& rows, const int& cols)
    : rows_(rows),
      cols_(cols),
      matrix_{std::vector(rows, std::vector<double>(cols))} {}

int Matrix::GetRows() const { return rows_; }
int Matrix::GetCols() const { return cols_; }

double& Matrix::operator()(int index_i, int index_j) {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}
const double& Matrix::operator()(int index_i, int index_j) const {
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

void Matrix::FillMatrixRandomValues(double min_random_value,
                                    double max_random_value) {
  std::uniform_real_distribution<double> dist(min_random_value,
                                              max_random_value);
  auto generate = [&]() -> double { return dist(gen_); };
  std::for_each(matrix_.begin(), matrix_.end(),
                [&](std::vector<double>& inner_vec) {
                  std::generate(inner_vec.begin(), inner_vec.end(), generate);
                });
}