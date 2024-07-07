#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(Constructors, DefaultConstructor) {
  S21Matrix M;
  EXPECT_EQ(M.GetRows(), 3);
  EXPECT_EQ(M.GetCols(), 3);
  ASSERT_FALSE(M.GetCols() == 0);
  ASSERT_FALSE(M.GetRows() == 0);
  ASSERT_TRUE(M.GetCols() == 3);
  ASSERT_TRUE(M.GetRows() == 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
}

TEST(Constructors, InvalidDimensionsConstructor) {
  EXPECT_THROW(S21Matrix M(0, 10), std::invalid_argument);
  EXPECT_THROW(S21Matrix M(10, 0), std::invalid_argument);
  EXPECT_THROW(S21Matrix M(-2, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix M(3, -3), std::invalid_argument);
  EXPECT_THROW(S21Matrix M(0, 0), std::invalid_argument);
  S21Matrix M(4, 5);
  EXPECT_THROW(M.GetElement(5, 5), std::out_of_range);
  EXPECT_THROW(M.GetElement(4, 6), std::out_of_range);
  EXPECT_THROW(M.GetElement(0, 5), std::out_of_range);
  EXPECT_THROW(M.GetElement(-1, 5), std::out_of_range);
  EXPECT_THROW(M.GetElement(4, 0), std::out_of_range);
  EXPECT_THROW(M.GetElement(4, -1), std::out_of_range);
  EXPECT_THROW(M.GetElement(-1, -1), std::out_of_range);
}

TEST(Constructors, ValidDimensionsConstructor) {
  S21Matrix M(4, 5);
  EXPECT_EQ(M.GetRows(), 4);
  EXPECT_EQ(M.GetCols(), 5);
  M.SetZero();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
}

TEST(Constructors, ValidConstructorCopy) {
  S21Matrix M_original(5, 9);
  S21Matrix M_copy(M_original);
  EXPECT_EQ(M_original.GetRows(), M_copy.GetRows());
  EXPECT_EQ(M_original.GetCols(), M_copy.GetCols());
  EXPECT_EQ(M_original.GetElement(2, 5), M_copy.GetElement(2, 5));
}

TEST(Constructors, ValidConstructorCopy2) {
  S21Matrix M_original(1, 1);
  S21Matrix M_copy(M_original);
  EXPECT_EQ(M_original.GetRows(), M_copy.GetRows());
  EXPECT_EQ(M_original.GetCols(), M_copy.GetCols());
  EXPECT_EQ(M_original.GetElement(0, 0), M_copy.GetElement(0, 0));
}

TEST(Constructors, InvalidConstructorCopy) {
  S21Matrix M_original(2, 2);
  S21Matrix M_copy(M_original);
  EXPECT_EQ(M_original.GetRows(), M_copy.GetRows());
  EXPECT_EQ(M_original.GetCols(), M_copy.GetCols());
  EXPECT_EQ(M_original.GetElement(0, 0), M_copy.GetElement(0, 0));
  EXPECT_THROW(M_original.GetElement(2, 2), std::out_of_range);
  EXPECT_THROW(M_copy.GetElement(2, 2), std::out_of_range);
}

TEST(Constructors, ValidConstructorCopyDefault) {
  S21Matrix M_original;
  S21Matrix M_copy(M_original);
  EXPECT_EQ(M_original.GetRows(), M_copy.GetRows());
  EXPECT_EQ(M_original.GetCols(), M_copy.GetCols());
  EXPECT_EQ(M_original.GetElement(1, 1), M_copy.GetElement(1, 1));
}

TEST(MoveConstructor, MoveDefaultMatrix) {
  S21Matrix M_original;
  S21Matrix M_moved(std::move(M_original));
  EXPECT_EQ(M_moved.GetRows(), 3);
  EXPECT_EQ(M_moved.GetCols(), 3);
  EXPECT_EQ(M_original.GetRows(), 0);
  EXPECT_EQ(M_original.GetCols(), 0);
  EXPECT_THROW(M_original.GetElement(0, 0), std::out_of_range);
}

TEST(MoveConstructor, ParametrsConstructor) {
  S21Matrix M_original(7, 10);
  S21Matrix M_moved(std::move(M_original));
  EXPECT_EQ(M_moved.GetRows(), 7);
  EXPECT_EQ(M_moved.GetCols(), 10);
  EXPECT_EQ(M_moved.GetElement(6, 9), 0.0);
  EXPECT_EQ(M_original.GetRows(), 0);
  EXPECT_EQ(M_original.GetCols(), 0);
  EXPECT_THROW(M_original.GetElement(0, 0), std::out_of_range);
}

TEST(AccessorsAndMutators, Cols) {
  S21Matrix M(4, 5);
  EXPECT_EQ(M.GetCols(), 5);
  M.SetCols(5);
  EXPECT_EQ(M.GetCols(), 5);
  M.SetCols(10);
  EXPECT_EQ(M.GetCols(), 10);
  for (int i = 0; i < M.GetRows(); ++i) {
    for (int j = 0; j < M.GetCols(); ++j) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
  M.SetCols(2);
  EXPECT_EQ(M.GetCols(), 2);
  for (int i = 0; i < M.GetRows(); ++i) {
    for (int j = 0; j < M.GetCols(); ++j) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
  EXPECT_THROW(M.SetCols(0), std::invalid_argument);
  EXPECT_THROW(M.SetCols(-1), std::invalid_argument);
}

TEST(AccessorsAndMutators, Rows) {
  S21Matrix M(4, 5);
  EXPECT_EQ(M.GetRows(), 4);
  M.SetRows(4);
  EXPECT_EQ(M.GetRows(), 4);
  M.SetRows(100);
  EXPECT_EQ(M.GetRows(), 100);
  for (int i = 0; i < M.GetRows(); ++i) {
    for (int j = 0; j < M.GetCols(); ++j) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
  M.SetRows(2);
  EXPECT_EQ(M.GetRows(), 2);
  for (int i = 0; i < M.GetRows(); ++i) {
    for (int j = 0; j < M.GetCols(); ++j) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
  EXPECT_THROW(M.SetRows(0), std::invalid_argument);
  EXPECT_THROW(M.SetRows(-1), std::invalid_argument);
}

TEST(AccessorsAndMutators, Element) {
  S21Matrix M(3, 3);
  EXPECT_EQ(M.GetElement(0, 0), 0.0);
  M.SetElement(0, 0, 1.0);
  EXPECT_EQ(M.GetElement(0, 0), 1.0);
  M.SetElement(0, 1, 2.0);
  EXPECT_EQ(M.GetElement(0, 1), 2.0);
  M.SetElement(0, 2, 3.0);
  EXPECT_EQ(M.GetElement(0, 2), 3.0);
  M.SetElement(1, 0, 4.0);
  EXPECT_EQ(M.GetElement(1, 0), 4.0);
  M.SetElement(1, 1, 5.0);
  EXPECT_EQ(M.GetElement(1, 1), 5.0);
  M.SetElement(1, 2, 6.0);
  EXPECT_EQ(M.GetElement(1, 2), 6.0);
  EXPECT_THROW(M.SetElement(-1, 0, 0.0), std::out_of_range);
  EXPECT_THROW(M.SetElement(0, -1, 0.0), std::out_of_range);
  EXPECT_THROW(M.SetElement(3, 0, 0.0), std::out_of_range);
  EXPECT_THROW(M.SetElement(0, 3, 0.0), std::out_of_range);
}

TEST(EqMatrix, EqualMethod) {
  S21Matrix M(3, 4);
  M.SetZero();
  S21Matrix M2;
  ASSERT_FALSE(M.EqMatrix(M2));
  M2.SetCols(4);
  ASSERT_TRUE(M.EqMatrix(M2));
  M.SetElement(0, 0, 1.000000000000001);
  M2.SetElement(0, 0, 1.000000000000001);
  M.SetElement(0, 1, -1.000000000000001);
  M2.SetElement(0, 1, -1.000000000000001);
  ASSERT_TRUE(M.EqMatrix(M2));
  ASSERT_TRUE(M.EqMatrix(M));
  M2.SetElement(0, 1, -1.000000000000009);
  ASSERT_FALSE(M.EqMatrix(M2));
  M.SetElement(0, 1, -1.000000000000009);
  M.SetElement(0, 0, 1.00000000000000019);
  M2.SetElement(0, 0, 1.0000000000000002);
  ASSERT_TRUE(M.EqMatrix(M2));
}

TEST(EqMatrix, EqualOperator) {
  S21Matrix M(3, 4);
  M.SetZero();
  S21Matrix M2;
  ASSERT_FALSE(M == M2);
  M2.SetCols(4);
  ASSERT_TRUE(M == M2);
  M.SetElement(0, 0, 1.000000000000001);
  M2.SetElement(0, 0, 1.000000000000001);
  M.SetElement(0, 1, -1.000000000000001);
  M2.SetElement(0, 1, -1.000000000000001);
  ASSERT_TRUE(M == M2);
  ASSERT_TRUE(M == M);
  M2.SetElement(0, 1, -1.000000000000009);
  ASSERT_FALSE(M == M2);
  M.SetElement(0, 1, -1.000000000000009);
  M.SetElement(0, 0, 1.00000000000000019);
  M2.SetElement(0, 0, 1.0000000000000002);
  ASSERT_TRUE(M == M2);
}

TEST(IndexingOperator, ReadAndWriteIndex) {
  S21Matrix M;
  M.SetZero();
  M.SetElement(0, 0, 1.000000000000001);
  M.SetElement(0, 1, -1.000000000000001);
  EXPECT_EQ(M(0, 0), 1.000000000000001);
  EXPECT_EQ(M(0, 1), -1.000000000000001);
  const S21Matrix &constM(M);
  EXPECT_EQ(constM(0, 0), 1.000000000000001);
  EXPECT_EQ(constM(0, 1), -1.000000000000001);
  EXPECT_THROW(constM(-1, 0), std::out_of_range);
  EXPECT_THROW(constM(0, -1), std::out_of_range);
  EXPECT_THROW(M(4, 0), std::out_of_range);
  EXPECT_THROW(M(0, 4), std::out_of_range);
}

TEST(AssignmentOperator, SelfCopyMove) {
  S21Matrix M;
  M(1, 1) = -5.123456789;
  S21Matrix M2 = M;
  M = M2;
  EXPECT_EQ(M(1, 1), -5.123456789);
  EXPECT_EQ(M(1, 1), M.GetElement(1, 1));
  M(0, 0) = 5.123456789;
  S21Matrix tmp;
  tmp = M;
  EXPECT_EQ(M(0, 0), 5.123456789);
  EXPECT_EQ(M(0, 0), M.GetElement(0, 0));
  M.SetZero();
  S21Matrix tmp2;
  tmp2 = tmp = M;
  EXPECT_EQ(M(0, 0), tmp2(0, 0));
  EXPECT_EQ(tmp2.GetRows(), 3);
  EXPECT_EQ(tmp2.GetCols(), 3);
  tmp2.SetElement(2, 2, 10.10);
  S21Matrix tmp3(3, 3);
  tmp3 = std::move(tmp2);
  EXPECT_EQ(tmp3(2, 2), 10.10);
}

TEST(MatrixAdditionDifference, SumSubMatrix) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 3);
  M.SetZero();
  M2.SetZero();
  M.SumMatrix(M2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(M.GetElement(i, j), 0.0);
    }
  }
  S21Matrix M3(3, 2);
  EXPECT_THROW(M + M3, std::invalid_argument);
  EXPECT_THROW(M - M3, std::invalid_argument);
  M3.SetCols(3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      M.SetElement(i, j, 5.0);
      M3(i, j) = 5.0;
    }
  }
  M = M + M3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(M.GetElement(i, j), 10.0);
    }
  }
  M = M - M3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(M.GetElement(i, j), 5.0);
    }
  }
}

TEST(Multiplication, MatrixNumMul) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix result(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = 2;
  b(1, 1) = 3;
  b(1, 2) = 4;
  result(0, 0) = 9.0;
  result(0, 1) = 11.0;
  result(0, 2) = 17.0;
  result(1, 0) = 12.0;
  result(1, 1) = 13.0;
  result(1, 2) = 22.0;
  result(2, 0) = 15.0;
  result(2, 1) = 15.0;
  result(2, 2) = 27.0;
  a.MulMatrix(b);
  EXPECT_EQ(a, result);
  a.SetZero();
  a.SetCols(2);
  a.SetRows(3);
  a(0, 0) = 1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  b(0, 0) = 1;
  b(0, 1) = 1;
  b(0, 2) = 1;
  b(1, 0) = 1;
  b(1, 1) = 1;
  b(1, 2) = 1;
  result.SetZero();
  result.SetCols(3);
  result.SetRows(3);
  result(0, 0) = 5.0;
  result(0, 1) = 5.0;
  result(0, 2) = 5.0;
  result(1, 0) = 7.0;
  result(1, 1) = 7.0;
  result(1, 2) = 7.0;
  result(2, 0) = 9.0;
  result(2, 1) = 9.0;
  result(2, 2) = 9.0;
  EXPECT_EQ(a * b, result);
  b.SetCols(5);
  b.SetRows(5);
  EXPECT_THROW(a * b, std::invalid_argument);
  EXPECT_ANY_THROW(a.MulNumber(std::nan("")));
  double num = 5.0;
  result.SetZero();
  result.SetCols(2);
  result.SetRows(3);
  result(0, 0) = 5.0;
  result(0, 1) = 20.0;
  result(1, 0) = 10.0;
  result(1, 1) = 25.0;
  result(2, 0) = 15.0;
  result(2, 1) = 30.0;
  S21Matrix result2(3, 2);
  result2 = a * num;
  EXPECT_EQ(result2, result);
  a.MulNumber(num);
  EXPECT_EQ(a, result);
}

TEST(OperatorsOverload, MultSumSub) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix result(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = 2;
  b(1, 1) = 3;
  b(1, 2) = 4;
  result(0, 0) = 9.0;
  result(0, 1) = 11.0;
  result(0, 2) = 17.0;
  result(1, 0) = 12.0;
  result(1, 1) = 13.0;
  result(1, 2) = 22.0;
  result(2, 0) = 15.0;
  result(2, 1) = 15.0;
  result(2, 2) = 27.0;
  a *= b;
  EXPECT_EQ(a, result);

  S21Matrix M(3, 3);
  S21Matrix M3(3, 3);
  S21Matrix M2(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      M.SetElement(i, j, 5.0);
      M3(i, j) = 5.0;
      M2(i, j) = 5.0;
    }
  }
  M += M3;
  M2 *= 5;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(M.GetElement(i, j), 10.0);
      EXPECT_EQ(M2.GetElement(i, j), 25.0);
    }
  }
  M -= M3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(M.GetElement(i, j), 5.0);
    }
  }
}

TEST(Transpose, TransposeTests) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a(2, 0) = 5.0;
  a(2, 1) = 6.0;
  S21Matrix result(a.Transpose());
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 6.0);
  S21Matrix M(3, 3);
  M(0, 0) = 1.0;
  M(0, 1) = 2.0;
  M(0, 2) = 3.0;
  M(1, 0) = 4.0;
  M(1, 1) = 5.0;
  M(1, 2) = 6.0;
  M(2, 0) = 7.0;
  M(2, 1) = 8.0;
  M(2, 2) = 9.0;
  S21Matrix result_sq = M.Transpose();
  EXPECT_DOUBLE_EQ(result_sq(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result_sq(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result_sq(0, 2), 7.0);
  EXPECT_DOUBLE_EQ(result_sq(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result_sq(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result_sq(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(result_sq(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result_sq(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(result_sq(2, 2), 9.0);
}

TEST(Determinant, DeterminantBaseCases) {
  S21Matrix M(1, 1);
  M(0, 0) = 2.123456789;
  EXPECT_TRUE(M.Determinant() == 2.123456789);
  S21Matrix M2(2, 2);
  M2(0, 0) = 10.0;
  M2(0, 1) = 11.0;
  M2(1, 0) = 11.0;
  M2(1, 1) = 11.0;
  EXPECT_TRUE(M2.Determinant() == -11.0);
}

TEST(Determinant, NotSquare) {
  S21Matrix M(2, 3);
  EXPECT_THROW(M.Determinant(), std::logic_error);
}

TEST(Determinant, DeterminantOtherCases) {
  S21Matrix M(3, 3);
  M(0, 0) = 1.0;
  M(0, 1) = 1.0;
  M(0, 2) = 1.0;
  M(1, 0) = 1.0;
  M(1, 1) = 1.0;
  M(1, 2) = 1.0;
  M(2, 0) = 1.0;
  M(2, 1) = 1.0;
  M(2, 2) = 1.0;
  EXPECT_TRUE(M.Determinant() == 0.0);
  M(0, 0) = 1.0;
  M(0, 1) = 7.0;
  M(0, 2) = 3.0;
  M(1, 0) = 10.0;
  M(1, 1) = 15.0;
  M(1, 2) = -10.0;
  M(2, 0) = 11.0;
  M(2, 1) = 15.0;
  M(2, 2) = 24.0;
  EXPECT_TRUE(M.Determinant() == -1985.0);
}

TEST(CalcComplements, SizeOneMatrixAndNotSquare) {
  S21Matrix M(1, 1);
  M(0, 0) = 2.123456;
  EXPECT_TRUE(M.CalcComplements()(0, 0) == 1.0);
  S21Matrix M2(2, 3);
  EXPECT_THROW(M2.CalcComplements(), std::logic_error);
}

TEST(CalcComplements, CalcComplementsCases) {
  S21Matrix M(3, 3);
  M(0, 0) = 5.0;
  M(0, 1) = 7.0;
  M(0, 2) = 1.0;
  M(1, 0) = -4.0;
  M(1, 1) = 1.0;
  M(1, 2) = 0.0;
  M(2, 0) = 2.0;
  M(2, 1) = 0.0;
  M(2, 2) = 3.0;
  S21Matrix M2(3, 3);
  M2(0, 0) = 3.0;
  M2(0, 1) = 12.0;
  M2(0, 2) = -2.0;
  M2(1, 0) = -21.0;
  M2(1, 1) = 13.0;
  M2(1, 2) = 14.0;
  M2(2, 0) = -1.0;
  M2(2, 1) = -4.0;
  M2(2, 2) = 33.0;
  EXPECT_TRUE(M2.EqMatrix(M.CalcComplements()));
  S21Matrix M3(2, 2);
  M3(0, 0) = 2.123456;
  M3(0, 1) = 3.123456;
  M3(1, 0) = 4.123456;
  M3(1, 1) = 5.123456;
  S21Matrix M4(2, 2);
  M4(0, 0) = 5.123456;
  M4(0, 1) = -4.123456;
  M4(1, 0) = -3.123456;
  M4(1, 1) = 2.123456;
  S21Matrix result = M3.CalcComplements();
  EXPECT_TRUE(M4 == result);
}

TEST(InverseMatrix, InverseMatrixValid) {
  S21Matrix M(1, 1);
  M(0, 0) = 2.123456789;
  EXPECT_DOUBLE_EQ(M.InverseMatrix()(0, 0), 0.47093023280729446);
  S21Matrix M2(2, 2);
  M2(0, 0) = 3.0;
  M2(0, 1) = 4.0;
  M2(1, 0) = 5.0;
  M2(1, 1) = 7.0;
  S21Matrix M3(2, 2);
  M3(0, 0) = 7.0;
  M3(0, 1) = -4.0;
  M3(1, 0) = -5.0;
  M3(1, 1) = 3.0;
  EXPECT_TRUE(M3.EqMatrix(M2.InverseMatrix()));
  S21Matrix M4(3, 3);
  M4(0, 0) = 2.0;
  M4(0, 1) = 5.0;
  M4(0, 2) = 7.0;
  M4(1, 0) = 6.0;
  M4(1, 1) = 3.0;
  M4(1, 2) = 4.0;
  M4(2, 0) = 5.0;
  M4(2, 1) = -2.0;
  M4(2, 2) = -3.0;
  S21Matrix M5(3, 3);
  M5(0, 0) = 1.0;
  M5(0, 1) = -1.0;
  M5(0, 2) = 1.0;
  M5(1, 0) = -38.0;
  M5(1, 1) = 41.0;
  M5(1, 2) = -34.0;
  M5(2, 0) = 27.0;
  M5(2, 1) = -29.0;
  M5(2, 2) = 24.0;
  EXPECT_TRUE(M5 == M4.InverseMatrix());
}

TEST(InverseMatrix, ZeroDeterminantAndNotSquare) {
  S21Matrix M2(2, 3);
  EXPECT_THROW(M2.InverseMatrix(), std::logic_error);
  S21Matrix M(2, 2);
  M(0, 0) = 2.0;
  M(0, 1) = 2.0;
  M(1, 0) = 2.0;
  M(1, 1) = 2.0;
  EXPECT_THROW(M.InverseMatrix(), std::logic_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}