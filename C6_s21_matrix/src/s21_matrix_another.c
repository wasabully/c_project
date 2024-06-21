#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (!s21_matrix_exists(A)) {
    error = 1;
  } else if (A->columns != A->rows || A->columns <= 1) {
    error = 2;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == 0) {
      int size = (A->rows) - 1;
      for (int i = 0; i < result->rows && error == 0; i++) {
        for (int j = 0; j < result->columns && error == 0; j++) {
          if (s21_member_norm(A->matrix[i][j])) {
            matrix_t temp;
            s21_create_matrix(size, size, &temp);
            s21_minor(A->matrix, temp.matrix, i, j, size + 1);
            result->matrix[i][j] =
                pow(-1, i + j) * s21_calculate_determinant(temp, size);
            s21_remove_matrix(&temp);
          } else {
            s21_remove_matrix(result);
            error = 2;
          }
        }
      }
    }
  }

  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;

  if (!s21_matrix_exists(A)) {
    error = 1;
  } else if (A->columns != A->rows) {
    error = 2;
  } else {
    int size = A->columns;
    *result = (double)s21_calculate_determinant(*A, size);
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double d = 0;
  if (A == NULL || A->matrix == NULL) error = 1;
  if (!error) {
    error = s21_determinant(A, &d);
    if (d == 0) error = 2;
  }
  if (!error) {
    if (A->rows == 1) {
      error = s21_create_matrix(1, 1, result);
      if (!error) result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else {
      matrix_t G = {0};
      s21_calc_complements(A, &G);
      matrix_t G_trans = {0};
      s21_transpose(&G, &G_trans);
      s21_mult_number(&G_trans, 1 / d, result);
      s21_remove_matrix(&G_trans);
      s21_remove_matrix(&G);
    }
  }
  return error;
}
