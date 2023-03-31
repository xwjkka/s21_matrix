#include "s21_matrix.h"

// void s21_output(matrix_t A) {
//   printf("%d %d\n", A.rows, A.columns);
//   for (int i = 0; i < A.rows; i++) {
//     for (int j = 0; j < A.columns; j++) {
//       printf("%lf ", A.matrix[i][j]);
//     }
//     printf("\n");
//   }
// }

void fill_matrix(matrix_t *A, double start, double step) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = start;
      start += step;
    }
  }
}

int s21_check_mtrx(matrix_t *A) {
  return A && A->matrix != NULL && (A->columns > 0 && A->rows > 0);
}

void s21_new_small_mtrx(matrix_t A, int row, int column, matrix_t *result) {
  int true_i = 0;
  int true_j = 0;
  if (!s21_create_matrix(A.rows - 1, A.columns - 1, result)) {
    for (int i = 0; i < A.rows; i++) {
      true_j = 0;
      if (i == row) {
        continue;
      }
      for (int j = 0; j < A.columns; j++) {
        if (j == column) {
          continue;
        }
        result->matrix[true_i][true_j] = A.matrix[i][j];
        true_j++;
      }
      true_i++;
    }
  }
}

double s21_recursion_det(matrix_t A) {
  matrix_t tmp = {0};
  double res = 0;
  if (A.rows == 1) {
    res = A.matrix[0][0];
  } else if (A.rows == 2) {
    res = (A.matrix[0][0] * A.matrix[1][1]) - (A.matrix[0][1] * A.matrix[1][0]);
  } else if (A.rows > 2) {
    int sign = 1;
    for (int i = 0; i < A.rows; i++) {
      s21_new_small_mtrx(A, i, 0, &tmp);
      double det = s21_recursion_det(tmp);
      res += sign * A.matrix[i][0] * det;
      sign *= -1;
      s21_remove_matrix(&tmp);
    }
  }
  return res;
}
