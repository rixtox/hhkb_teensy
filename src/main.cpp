#include "main.h"

extern "C" int main(void) {
  setup();
  while (1) {
    loop();
    yield();
  }
}

void setup() {
  BTSERIAL.begin(BTBAUD);
  Keyboard.begin();
  pinMode(KEY, INPUT_PULLUP);
  pinMode(HYS, OUTPUT);
  pinMode(ROWA, OUTPUT);
  pinMode(ROWB, OUTPUT);
  pinMode(ROWC, OUTPUT);
  pinMode(COLA, OUTPUT);
  pinMode(COLB, OUTPUT);
  pinMode(COLC, OUTPUT);
  pinMode(ENAB, OUTPUT);
  pinMode(RSBT, OUTPUT);
}

void loop() {
  matrix_scan();
  matrix_exec();
}
