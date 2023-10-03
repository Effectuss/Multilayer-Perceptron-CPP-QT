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

std::size_t Matrix::GetRows() const { return rows_; }

std::size_t Matrix::GetCols() const { return cols_; }

double &Matrix::operator()(std::size_t index_i, std::size_t index_j) {
  if (index_i >= rows_ || index_j >= cols_) {
    throw std::invalid_argument(
        "The indexes cannot be negative or bigger than amount of cols or "
        "rows!");
  }
  return matrix_[index_i][index_j];
}

const double &Matrix::operator()(std::size_t index_i,
                                 std::size_t index_j) const {
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

  std::size_t row = matrix.GetRows();
  std::size_t cols = matrix.GetCols();

  for (std::size_t i = 0; i < row; ++i) {
    for (std::size_t j = 0; j < cols; ++j) {
      vector_res[i] += matrix(i, j) * vector_column[j];
    }
  }
}

const std::vector<double> &Matrix::GetVectorByRows(std::size_t row) const {
  if (row >= rows_) {
    throw std::runtime_error("Incorrect number of row");
  }

  return matrix_[row];
}
std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      out << matrix(i, j) << " ";
      if (out.fail()) {
        throw std::runtime_error("Error output matrix");
      }
    }
    out << "\n";
  }
  return out;
}

std::istream &operator>>(std::istream &input, Matrix &matrix) {
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      if (!(input >> matrix(i, j))) {
        throw std::runtime_error("Error input matrix!");
      }
    }
  }
  return input;
}
