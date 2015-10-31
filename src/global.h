#include "WProgram.h"

#define GLOBAL

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define BTSERIAL Serial1
#define BTBAUD 9600

#define KEY 3
#define HYS 4
#define ROWA 5
#define ROWB 6
#define ROWC 7
#define COLA 8
#define COLB 9
#define COLC 10
#define ENAB 11
#define RSBT 14

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define SET_BIT(var,pos) ((var) |= (1<<(pos)))
#define CLR_BIT(var,pos) ((var) &= ~(1<<(pos)))

#define USB_DRIVER_EEPROM 0
#define BLUETOOTH_DRIVER_EEPROM 1

typedef struct keypos_t {
  int row;
  int col;
} keypos_t;

typedef struct keyevent_t {
  keypos_t key;
  int press;
} keyevent_t;

typedef int matrix_row_t;

extern int usb_driver_enabled;
extern int bluetooth_driver_enabled;

extern matrix_row_t* matrix;
extern matrix_row_t* matrix_prev;

#include "keymaps.h"
