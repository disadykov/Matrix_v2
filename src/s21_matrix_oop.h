#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double **matrix_;

  /// @brief Выделение памяти под матрицу
  void NewMatrix();

  /// @brief Освобождение памяти, выделенной под матрицу
  void DeleteMatrix();

  /// @brief Проверка размеров матрицы
  void ValidateDimensions() const;

  /// @brief Вычисление минора
  /// @param row номер строки
  /// @param col номер столбца
  /// @return Минор матрицы
  S21Matrix MinorMatrix(int row, int col) const;

 public:
  /// @brief Базовый конструктор, инициализирующий матрицу некоторой заранее
  /// заданной размерностью (3x3)
  S21Matrix();

  /// @brief Параметризированный конструктор с количеством строк и столбцов
  /// @param rows кол-во строк
  /// @param cols кол-во столбцов
  S21Matrix(int rows, int cols);

  /// @brief Конструктор копирования
  /// @param other матрица из которой копируем
  S21Matrix(const S21Matrix &other);

  /// @brief Конструктор переноса
  /// @param other матрица которую переносим
  S21Matrix(S21Matrix &&other);

  ~S21Matrix();  // Деструктор

  /// @brief Инициализация матрицы нулями
  void SetZero();

  /// @brief Получаем количество строк матрицы
  /// @return кол-во строк матрицы из приватного поля класса
  int GetRows() const;

  /// @brief Получаем количество столбцов матрицы
  /// @return кол-во столбцов матрицы из приватного поля класса
  int GetCols() const;

  /// @brief Получаем значение элемента матрицы
  /// @param rows номер строки
  /// @param cols номер столбца
  /// @return возвращаем значение элемента матрицы
  double GetElement(int rows, int cols) const;

  /// @brief устанавливаем кол-во столбцов
  /// @param cols Количество столбцов
  void SetCols(int cols);

  /// @brief устанавливаем кол-во строк
  /// @param rows Количество строк
  void SetRows(int rows);

  /// @brief Устанавливает значение элемента
  /// @param rows позиция в строке
  /// @param cols позиция в столбце
  /// @param value значение
  void SetElement(int rows, int cols, double value);

  /// @brief Проверяет матрицы на равенство
  /// @param other матрица, с которой сравниваем
  /// @return true - матрицы равны, false - не равны
  bool EqMatrix(const S21Matrix &other) const;

  /// @brief Проверка матрицы на равенство через оператор ==
  /// @param other матрица, с которой сравниваем
  /// @return true - матрицы равны, false - не равны
  bool operator==(const S21Matrix &other) const;

  /// @brief Возвращает значение элемента матрицы по индексу
  /// @param i элемент строки
  /// @param j элемент столбца
  /// @return значение, которое расположено по индексу
  double &operator()(int i, int j);

  /// @brief Возвращает значение элемента матрицы по индексу (константный метод)
  /// @param i элемент строки
  /// @param j элемент столбца
  /// @return значение, которое расположено по индексу
  const double &operator()(int i, int j) const;

  /// @brief Оператор присваивания
  /// @param other матрица, которую присваиваем
  /// @return ссылка на текущую матрицу после перемещения
  S21Matrix &operator=(const S21Matrix &other);

  /// @brief Оператор присваивания как rvalue (matrix = std::move(matrix);)
  /// @param other матрица, которую присваиваем
  /// @return ссылка на текущую матрицу после перемещения
  S21Matrix &operator=(S21Matrix &&other);

  /// @brief Сложение матриц
  /// @param other матрица, которую прибавляем
  void SumMatrix(const S21Matrix &other);

  /// @brief Сложение матриц через оператор +
  /// @param other матрица, которую прибавляем
  S21Matrix operator+(const S21Matrix &other) const;

  /// @brief Вычитание матриц
  /// @param other матрица, которую прибавляем
  void SubMatrix(const S21Matrix &other);

  /// @brief Вычитание матриц через оператор -
  /// @param other матрица, которую прибавляем
  S21Matrix operator-(const S21Matrix &other) const;

  /// @brief Умножение матрицы на число
  /// @param num число, на которое умножаем
  void MulNumber(const double num);

  /// @brief Умножение матрицы на число через оператор *
  /// @param num число, на которое умножаем
  S21Matrix operator*(double num) const;

  /// @brief Умножение матриц
  /// @param other матрица на которую умножаем
  void MulMatrix(const S21Matrix &other);

  /// @brief Умножение матрицы через оператор *
  /// @param other матрица на которую умножаем
  S21Matrix operator*(const S21Matrix &other) const;

  /// @brief Операторы с присваиванием
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);

  /// @brief Транспонирование матрицы
  S21Matrix Transpose() const;

  /// @brief Вычисляет и возвращает определитель текущей матрицы
  double Determinant() const;

  /// @brief Вычисляет матрицу алгебраических дополнений текущей матрицы и
  /// возвращает ее
  S21Matrix CalcComplements() const;

  /// @brief Вычисляет обратную матрицу и возвращает ее
  S21Matrix InverseMatrix() const;
};

#endif  // SRC_S21_MATRIX_OOP_H_