#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 0;
  if (result != NULL && rows > 0 && columns > 0) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          flag = 1;
          for (int j = i - 1; j <= 0; j--) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          break;
        }
      }
    } else {
      flag = 1;
    }
  } else {
    if (result != NULL) {
      result->rows = rows;
      result->columns = columns;
      result->matrix = NULL;
    }
    flag = 1;
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (s21_check_mtrx(A) && s21_check_mtrx(B) && A->rows == B->rows &&
      A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((fabs((A->matrix)[i][j] - (B->matrix)[i][j]) > 1e-7)) {
          flag = FAILURE;
          break;
        }
      }
    }
  } else {
    flag = FAILURE;
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A) || !s21_check_mtrx(B)) {
    flag = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A) || !s21_check_mtrx(B)) {
    flag = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    flag = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A)) {
    flag = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A) || !s21_check_mtrx(B)) {
    flag = 1;
  } else if (A->columns != B->rows) {
    flag = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A)) {
    flag = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A)) {
    flag = 1;
  } else if (A->rows != A->columns) {
    flag = 2;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == 0) {
      matrix_t minor_mtrx = {0};
      int row = A->rows;
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
        row--;
      }
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < result->columns; j++) {
          s21_new_small_mtrx(*A, i, j, &minor_mtrx);
          double det = 0;
          s21_determinant(&minor_mtrx, &det);
          result->matrix[i][j] = pow(-1, i + j) * det;
          s21_remove_matrix(&minor_mtrx);
        }
      }
    } else {
      flag = 1;
    }
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = 0;
  if (s21_check_mtrx(A) && result) {
    if (A->rows == A->columns) {
      *result = s21_recursion_det(*A);
    } else {
      flag = 2;
    }
  } else {
    flag = 1;
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!s21_check_mtrx(A)) {
    flag = 1;
  } else if (A->rows != A->columns) {
    flag = 2;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0.0) {
      flag = 2;
    } else {
      s21_calc_complements(A, result);
      matrix_t tmp = {0};

      s21_transpose(result, &tmp);
      s21_remove_matrix(result);

      s21_mult_number(&tmp, tmp.rows == 1 ? pow(det, -2) : 1.0 / det, result);

      s21_remove_matrix(&tmp);
    }
  }
  return flag;
}
