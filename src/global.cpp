#include "global.h"

matrix_row_t* matrix = new matrix_row_t[MATRIX_ROWS];
matrix_row_t* matrix_prev = new matrix_row_t[MATRIX_ROWS];

int current_keymap = 1;
int fn_mode = 0;
