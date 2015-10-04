#if !defined(GLOBAL)
  #include "global.h"
#endif
#include "action.h"

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

void matrix_scan();
void matrix_exec();
