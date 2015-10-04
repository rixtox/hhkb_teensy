#include "matrix.h"

void matrix_scan() {
  // swap matrix and matrix_prev
  matrix_row_t* tmp;

  tmp = matrix_prev;
  matrix_prev = matrix;
  matrix = tmp;

  static int row, col;
  for (row = 0; row < MATRIX_ROWS; ++row) {
    for (col = 0; col < MATRIX_COLS; ++col) {
      KEY_SELECT(row, col);
      delayMicroseconds(5);

      if (CHECK_BIT(matrix_prev[row], col)) {
        KEY_PREV_ON();
      }
      delayMicroseconds(5);

      KEY_ENABLE();
      delayMicroseconds(5);

      if (KEY_STATE()) {
        CLR_BIT(matrix[row], col);
      } else {
        SET_BIT(matrix[row], col);
      }
      delayMicroseconds(5);

      KEY_PREV_OFF();
      KEY_UNABLE();
      delayMicroseconds(5);
    }
  }
}

void matrix_exec() {
  static int row, col;
  static matrix_row_t matrix_row, matrix_row_diff;
  for (row = 0; row < MATRIX_ROWS; ++row) {
    matrix_row = matrix[row];
    matrix_row_diff = matrix_row ^ matrix_prev[row];

    if (matrix_row_diff) {
      for (col = 0; col < MATRIX_COLS; ++col) {
        if (CHECK_BIT(matrix_row_diff, col)) {
          send_event((keyevent_t) {
            .key = (keypos_t) { .row = row, .col = col },
            .press = CHECK_BIT(matrix_row, col)
          });
        }
      }
    }
  }
}
