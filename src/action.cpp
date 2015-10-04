#include "action.h"

void send_event(keyevent_t e) {
  int keycode;
  if (fn_mode) {
    int trans_keycode = keymaps[current_keymap][e.key.row][e.key.col];
    if (!e.press && trans_keycode == KEY_FN0) {
      fn_mode = 0;
      return;
    }
    keycode = keymaps[0][e.key.row][e.key.col];
    if (keycode == KEY_TRNS) {
      keycode = trans_keycode;
    }
  } else {
    keycode = keymaps[current_keymap][e.key.row][e.key.col];
  }
  if (keycode >= 0xC000) {
    /* Macro keys */
    if (e.press && keycode == KEY_FN0) {
      fn_mode = 1;
    }
    return;
  }
  if (e.press) {
    usb_keyboard_press_keycode(keycode);
  } else {
    usb_keyboard_release_keycode(keycode);
  }
}
