#include "WProgram.h"

#define GLOBAL

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define KEY 3
#define HYS 4
#define ROWA 5
#define ROWB 6
#define ROWC 7
#define COLA 8
#define COLB 9
#define COLC 10
#define ENAB 11

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define SET_BIT(var,pos) ((var) |= (1<<(pos)))
#define CLR_BIT(var,pos) ((var) &= ~(1<<(pos)))

typedef struct keypos_t {
  int row;
  int col;
} keypos_t;

typedef struct keyevent_t {
  keypos_t key;
  int press;
} keyevent_t;

typedef int matrix_row_t;

extern matrix_row_t* matrix;
extern matrix_row_t* matrix_prev;

extern int current_keymap;
extern int fn_mode;

#include "keymaps.h"
