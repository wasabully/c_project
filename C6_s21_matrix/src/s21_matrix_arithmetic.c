#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) error = 1;
  if (!error && A->rows == B->rows && A->columns == B->columns) {
    error = s21_create_matrix(A->rows, B->columns, result);
  } else
    error = 2;
  if (!error) {
    for (int i = 0; i < A->rows && !error; i++)
      for (int j = 0; j < A->columns && !error; j++) {
        if (s21_member_norm(A->matrix[i][j]) &&
            s21_member_norm(B->matrix[i][j]) &&
            s21_member_norm(A->matrix[i][j] + B->matrix[i][j]))
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        else {
          s21_remove_matrix(result);
          error = 2;
        }
      }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) {
    error = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = 2;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);

    if (error == 0) {
      for (int i = 0; i < A->rows && error == 0; i++) {
        for (int j = 0; j < A->columns && error == 0; j++) {
          double diff = A->matrix[i][j] - B->matrix[i][j];
          if (s21_member_norm(A->matrix[i][j]) &&
              s21_member_norm(B->matrix[i][j]) && s21_member_norm(diff)) {
            result->matrix[i][j] = diff;
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

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;

  if (!(A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0))
    error = 1;
  if (!error) {
    error = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (!s21_matrix_exists(A) || !s21_matrix_exists(B)) {
    error = 1;
  } else if (A->columns != B->rows) {
    error = 2;
  } else {
    error = s21_create_matrix(A->rows, B->columns, result);
    if (error == 0) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->columns; ++j) {
          result->matrix[i][j] = 0;
          for (int g = 0; g < B->rows; g++) {
            result->matrix[i][j] += A->matrix[i][g] * B->matrix[g][j];
          }
        }
      }
    }
  }

  return error;
}