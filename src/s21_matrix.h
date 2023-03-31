#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/**
 * @brief Создание матриц
 * @param row строка n
 * @param columns столбец m
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief Очистка матриц
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief Сравнение матриц
 * @return 1 - SUCCESS, 0 - FAILURE
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/**
 * @brief Сложение матриц
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Вычитание матриц
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Умножение матрицы на число
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief Умножение двух матриц
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Транспонирование матрицы
 * Транспонирование матрицы А заключается в замене строк этой матрицы ее
 * столбцами с сохранением их номеров.
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * @brief Минор матрицы и матрица алгебраических дополнений.
 * Минором M(i,j) называется определитель (n-1)-го порядка, полученный
 * вычёркиванием из матрицы A i-й строки и j-го столбца.
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/**
 * @brief Определитель матрицы.
 * Определитель (детерминант) - это число, которое ставят в соответствие каждой
 * квадратной матрице и вычисляют из элементов по специальным формулам.
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_determinant(matrix_t *A, double *result);

/**
 * @brief Обратная матрица.
 * Tip: Обратной матрицы не существует, если определитель равен 0.
 * @return 0 - OK, 1 - Ошибка, некорректная матрица, 2 - Ошибка вычисления
 * (несовпадающие размеры матриц; матрица, для которой нельзя провести
 * вычисления и т.д.)
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// --------------------------------------------------- help

/**
 * @brief Вывод матрицы
 */
void s21_output(matrix_t A);

/**
 * @brief Проверяет выделилась ли память на каждый из массивов в матрице
 * @return 1 - OK, 0 - Ошибка,
 */
int s21_check_mtrx(matrix_t *A);

/**
 * @brief Убирает ряд и столбец из матрицы A и записывает в result
 */
void s21_new_small_mtrx(matrix_t A, int row, int column, matrix_t *result);

/**
 * @brief Считает определитель
 */
double s21_recursion_det(matrix_t A);

int s21_is_valid_matrix(matrix_t *A);
int s21_is_ptr(const matrix_t *A);
int s21_is_same_matrix(matrix_t *A, matrix_t *B);
void fill_matrix(matrix_t *A, double start, double step);
// double s21_minor(matrix_t A);
#endif // SRC_MATRIX_H_
