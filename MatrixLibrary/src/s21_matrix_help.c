#include "s21_matrix.h"

int s21_matrix_exists(matrix_t *matr_struct) {
  int error = 1;

  if (matr_struct == NULL || matr_struct->matrix == NULL ||
      matr_struct->columns <= 0 || matr_struct->rows <= 0) {
    error = 0;
  } else {
    for (int i = 0; i < matr_struct->rows && error; i++) {
      if (matr_struct->matrix[i] == NULL) {
        error = 0;
      }
    }
  }

  return error;
}

int s21_member_norm(double matr_member) {
  int error = 1;

  if (isinf(matr_member) || isnan(matr_member)) {
    error = 0;
  }

  return error;
}

void s21_minor(double **mat, double **temp, int skip_row, int skip_col, int n) {
  int i = 0, j = 0;

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (row != skip_row && col != skip_col) {
        temp[i][j++] = mat[row][col];

        if (j == n - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

double s21_calculate_determinant(matrix_t mat, int size) {
  double determinant = 0;

  if (size == 1) {
    determinant = mat.matrix[0][0];
  } else {
    matrix_t temp;
    if (s21_create_matrix(size - 1, size - 1, &temp) == 0) {
      int sign = 1;

      for (int cur_col = 0; cur_col < size; cur_col++) {
        s21_minor(mat.matrix, temp.matrix, 0, cur_col, size);
        determinant += sign * mat.matrix[0][cur_col] *
                       s21_calculate_determinant(temp, size - 1);

        sign = -sign;
      }
      s21_remove_matrix(&temp);
    }
  }
  return determinant;
}