#include "matrix.h"
std::random_device Matrix::rd_;

std::mt19937 Matrix::gen_(rd_());

bool Matrix::IsCorrectIndex(int rows, int cols) { return rows > 0 && cols > 0; }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!IsCorrectIndex(rows, cols)) {
    throw std::invalid_argument("Incorrect size for matrix");
  }
  matrix_ = std::vector(rows, std::vector<double>(cols));
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

double &Matrix::operator()(int index_i, int index_j) {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}

const double &Matrix::operator()(int index_i, int index_j) const {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}

void Matrix::FillMatrixRandomValues(double min_random_value,
                                    double max_random_value) {
  std::uniform_real_distribution<double> dist(min_random_value,
                                              max_random_value);

  auto generate = [&]() -> double { return dist(gen_); };

  std::for_each(matrix_.begin(), matrix_.end(),
                [&](std::vector<double> &inner_vec) {
                  std::generate(inner_vec.begin(), inner_vec.end(), generate);
                });
}
void Matrix::MultiplyByVector(const Matrix &matrix,
                              const std::vector<double> &vector_column,
                              std::vector<double> &vector_res) {
  if (matrix.GetCols() != vector_column.size()) {
    throw std::invalid_argument("Error multiply!");
  }

  int row = matrix.GetRows();
  int cols = matrix.GetCols();

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < cols; ++j) {
      vector_res[i] += matrix(i, j) * vector_column[j];
    }
  }
}
