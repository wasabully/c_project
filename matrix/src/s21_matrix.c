#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;

  if (rows <= 0 || columns <= 0) {
    error = 1;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      error = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          error = 1;
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
        }
      }
      if (error == 0) {
        result->rows = rows;
        result->columns = columns;
      }
    }
  }

  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;

  if (A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
      A->columns > 0) {
    for (int i = 0; i < A->rows && error; i++) {
      for (int j = 0; j < A->columns && error; j++) {
        if ((int)(round(A->matrix[i][j] * 1e7)) !=
            (int)(round(B->matrix[i][j] * 1e7))) {
          error = FAILURE;
        }
      }
    }
  } else {
    error = FAILURE;
  }

  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (!s21_matrix_exists(A)) {
    error = 1;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);

    if (error == 0) {
      for (int i = 0; i < A->rows && error != 2; i++) {
        for (int j = 0; j < A->columns && error != 2; j++) {
          double value = A->matrix[i][j];

          if (s21_member_norm(value)) {
            result->matrix[j][i] = value;
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