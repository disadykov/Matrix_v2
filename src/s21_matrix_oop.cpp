#include "s21_matrix_oop.h"

#include <iostream>
void S21Matrix::NewMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}
void S21Matrix::SetZero() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}
void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}
void S21Matrix::ValidateDimensions() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument(
        "Error: Invalid matrix dimensions, rows or cols <= 0");
  }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
  NewMatrix();
  SetZero();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  ValidateDimensions();
  NewMatrix();
  SetZero();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  NewMatrix();
  // копируем элементы из other матрицы в текущую
  for (int i = 0; i < rows_; i++) {
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

double S21Matrix::GetElement(int rows, int cols) const {
  if (rows < 0 || rows >= rows_ || cols < 0 || cols >= cols_) {
    throw std::out_of_range("Invalid row or column index.");
  }
  return matrix_[rows][cols];
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("Invalid number of columns.");
  }
  if (cols == cols_) {
    return;
  } else {
    double **new_matrix = new double *[rows_]();
    for (int i = 0; i < rows_; i++) {
      new_matrix[i] = new double[cols]();
      for (int j = 0; j < cols; j++) {
        new_matrix[i][j] = 0.0;  // Инициализируем нулями
      }
    }
    // Копируем элементы матрицы
    int new_cols = std::min(cols, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < new_cols; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
    DeleteMatrix();
    matrix_ = new_matrix;
    cols_ = cols;
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Invalid number of rows.");
  }
  if (rows == rows_) {
    return;
  } else {
    double **new_matrix = new double *[rows]();
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new double[cols_]();
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = 0.0;  // Инициализируем нулями
      }
    }
    // Копируем элементы матрицы
    int new_rows = std::min(rows, rows_);
    for (int i = 0; i < new_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
    DeleteMatrix();
    matrix_ = new_matrix;
    rows_ = rows;
  }
}

void S21Matrix::SetElement(int rows, int cols, double value) {
  if (rows < 0 || rows >= rows_ || cols < 0 || cols >= cols_) {
    throw std::out_of_range("Invalid row or column index.");
  }
  matrix_[rows][cols] = value;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool eq_falg = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    eq_falg = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        // Проверка 15ти знаков после запятой
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) >
            std::numeric_limits<double>::epsilon()) {
          eq_falg = false;
          break;
        }
      }
    }
  }
  return eq_falg;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Matrix index is out of range.");
  }
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Matrix index is out of range.");
  }
  return matrix_[i][j];
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix matrix_tmp(other);  // Создаем временный объект

    // поменять поля матрицы местами
    std::swap(matrix_, matrix_tmp.matrix_);
    std::swap(rows_, matrix_tmp.rows_);
    std::swap(cols_, matrix_tmp.cols_);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    // Очистить текущее содержимое
    DeleteMatrix();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    // Зануляем, чтобы предотвратить двойное удаление
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrix dimensions are incompatible for addition.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrix dimensions are incompatible for addition.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

void S21Matrix::MulNumber(const double num) {
  if (num != num) {
    throw std::invalid_argument("Incorrect argument for multiplication.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix dimensions are incompatible for multiplication.");
  }
  S21Matrix result;
  result.SetZero();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  *this = *this * num;
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  *this = *this * other;
  return *this;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::MinorMatrix(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minorRow = 0;
  for (int i = 0; i < rows_; i++) {
    // Пропускаем выбранную строку
    if (i == row) {
      continue;
    }
    int minorCol = 0;
    for (int j = 0; j < cols_; j++) {
      // Пропускаем выбранный столбец
      if (j == col) {
        continue;
      }
      minor.matrix_[minorRow][minorCol] = matrix_[i][j];
      ++minorCol;
    }
    ++minorRow;
  }
  return minor;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is ​​not square.");
  }
  if (rows_ == 1) {
    // если матрица 1x1, то определитель равен единственному элементу
    return matrix_[0][0];
  } else if (rows_ == 2) {
    // // Определитель матрицы 2х2
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    // Рекурсивное вычисление методом Лапласа
    double determinant = 0;
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = MinorMatrix(0, j);
      double minorDeterminant = minor.Determinant();
      determinant += matrix_[0][j] * std::pow(-1.0, j) * minorDeterminant;
    }
    return determinant;
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is ​​not square.");
  } else {
    // S21Matrix result(rows_, cols_);
    if (rows_ > 1) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          // Вычисление матрицы миноров
          S21Matrix minor_matrix = MinorMatrix(i, j);
          double minorDeterminant = minor_matrix.Determinant();
          // Вычисление алгебраического дополнения
          double complement = std::pow(-1.0, i + j) * minorDeterminant;
          result.matrix_[i][j] = complement;
        }
      }
    } else {
      // минор (или алгебраическое дополнение) любого элемента единичной матрицы
      // (любого порядка), стоящего на главной диагонали, всегда равен 1
      result.matrix_[0][0] = 1.0;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is ​​not square.");
  }
  double determinant = Determinant();
  if (determinant == 0) {
    throw std::logic_error("Determinant equal to zero");
  }
  S21Matrix complements = CalcComplements();
  S21Matrix result = complements.Transpose();
  double scalar = 1.0 / determinant;
  result.MulNumber(scalar);

  return result;
}