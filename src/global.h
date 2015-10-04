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

#define KEY_SELECT(row, col) \
  digitalWrite(ROWA, CHECK_BIT(row, 0));\
  digitalWrite(ROWB, CHECK_BIT(row, 1));\
  digitalWrite(ROWC, CHECK_BIT(row, 2));\
  digitalWrite(COLA, CHECK_BIT(col, 0));\
  digitalWrite(COLB, CHECK_BIT(col, 1));\
  digitalWrite(COLC, CHECK_BIT(col, 2))\

#define KEY_PREV_ON() digitalWrite(HYS, HIGH)
#define KEY_PREV_OFF() digitalWrite(HYS, LOW)
#define KEY_ENABLE() digitalWrite(ENAB, LOW)
#define KEY_UNABLE() digitalWrite(ENAB, HIGH)
#define KEY_STATE() digitalRead(KEY)

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
