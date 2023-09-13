#include "matrix.h"

std::random_device Matrix::rd_;

std::mt19937 Matrix::gen_(rd_());

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!IsCorrectIndex(rows, cols)) {
    throw std::invalid_argument("Incorrect size for matrix");
  }
  matrix_ = std::vector(rows, std::vector<double>(cols));
}

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

Matrix Matrix::MultiplyByMatrix(const Matrix& other_matrix) const {
  if (cols_ != other_matrix.rows_) {
    throw std::runtime_error(
        "The amount of cols in matrix have to equal rows in other matrix!");
  }

  Matrix result_matrix = std::move(Matrix(rows_, other_matrix.cols_));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other_matrix.cols_; ++j) {
      for (int k = 0; k < other_matrix.rows_; ++k) {
        result_matrix.matrix_[i][j] +=
            matrix_[i][k] * other_matrix.matrix_[k][j];
      }
    }
  }

  return result_matrix;
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

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
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

std::istream& operator>>(std::istream& in, Matrix& matrix) {
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      if (!(in >> matrix(i, j))) {
        throw std::runtime_error("Error input matrix!");
      }
    }
  }
  return in;
}

Matrix Matrix::operator*(const Matrix& other_matrix) const {
  return this->MultiplyByMatrix(other_matrix);
}

std::vector<double>& Matrix::operator[](int row_index) {
  if (row_index >= rows_ || row_index < 0) {
    throw std::invalid_argument("Incorrect value of rows index");
  }

  return matrix_[row_index];
}

const std::vector<double>& Matrix::operator[](int row_index) const {
  if (row_index >= rows_ || row_index < 0) {
    throw std::invalid_argument("Incorrect value of rows index");
  }
  return matrix_[row_index];
}

bool Matrix::IsCorrectIndex(int rows, int cols) { return rows > 0 && cols > 0; }


void Matrix::SumVector(std::vector<double>& vec_a,
                       const std::vector<double>& vec_b) {
  for (int i = 0; i < vec_a.size(); ++i) {
    vec_a[i] += vec_b[i];
  }
}

void Matrix::MultiplyByVector(const Matrix& matrix,
                              const std::vector<double>& vec,
                              std::vector<double>& res_vec) {
  if (matrix.GetCols() != vec.size()) {
    throw std::invalid_argument("Error multiply!");
  }
  int row = matrix.GetRows();
  int cols = matrix.GetCols();

  for (int i = 0; i < row; ++i) {
    double res_sum = 0.0;
    for (int j = 0; j < cols; ++j) {
      res_sum += matrix(i, j) * vec[j];
    }
    res_vec[i] = res_sum;
  }
}

void Matrix::MultiplyTransposeMatrixByVector(const Matrix& matrix,
                                             const std::vector<double>& vec,
                                             std::vector<double>& res) {
  if (matrix.GetRows() != vec.size()) {
    throw std::invalid_argument("Error multiply!");
  }

  int row = matrix.GetRows();
  int cols = matrix.GetCols();

  for (int i = 0; i < cols; ++i) {
    double res_sum = 0.0;
    for (int j = 0; j < row; ++j) {
      res_sum += matrix(j, i) * vec[j];
    }
    res[i] = res_sum;
  }
}
