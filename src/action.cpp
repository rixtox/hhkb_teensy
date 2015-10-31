#include "action.h"

int fn_mode = 0;
int current_keymap = 1;

extern uint8_t keyboard_keys[];
extern uint8_t keyboard_media_keys;
extern uint8_t keyboard_modifier_keys;

extern int usb_driver_enabled;
extern int bluetooth_driver_enabled;

int any_key_pressed() {
  int i;
  if (keyboard_modifier_keys || keyboard_modifier_keys)
    return 1;
  for (i = 0; i < 6; i++)
    if (keyboard_keys[i]) return 1;
  return 0;
}

void bt_keyboard_send() {
  if (!bluetooth_driver_enabled)
    return;
  BTSERIAL.write(0xFD);
  BTSERIAL.write(keyboard_modifier_keys);
  BTSERIAL.write((byte)0x00);
  BTSERIAL.write(keyboard_keys[0]);
  BTSERIAL.write(keyboard_keys[1]);
  BTSERIAL.write(keyboard_keys[2]);
  BTSERIAL.write(keyboard_keys[3]);
  BTSERIAL.write(keyboard_keys[4]);
  BTSERIAL.write(keyboard_keys[5]);
}

void press_key(int keycode) {
  usb_keyboard_press_keycode(keycode);
  bt_keyboard_send();
}

void release_key(int keycode) {
  usb_keyboard_release_keycode(keycode);
  bt_keyboard_send();
}

void release_all() {
  usb_keyboard_release_all();
  bt_keyboard_send();
}

int key_macro_fn(int &keycode, keyevent_t &event) {
  static int pressed_on_fn_mode[20];
  int fn_keycode, i;
  if (keycode == KEY_FN0) {
    fn_mode = event.press;
    return 0;
  } else if (fn_mode && event.press) {
    fn_keycode = keymaps[0][event.key.row][event.key.col];
    if (fn_keycode != KEY_TRNS) {
      for (i = 0; i < 20; i++) {
        if (!pressed_on_fn_mode[i]) {
          pressed_on_fn_mode[i] = fn_keycode;
          break;
        }
      }
      keycode = fn_keycode;
    }
  } else if (!event.press) {
    fn_keycode = keymaps[0][event.key.row][event.key.col];
    for (i = 0; i < 20; i++) {
      if (pressed_on_fn_mode[i] == fn_keycode) {
        keycode = fn_keycode;
        pressed_on_fn_mode[i] = 0;
        break;
      }
    }
  }
  return 1;
}

int key_macro_layer(int &keycode, keyevent_t &event) {
  int keymap;
  if (event.press && keycode >= KEY_LYR0 && keycode <= KEY_LYR9) {
    keymap = keycode - KEY_LYR0 + 1;
    if (keymap > 0 && keymap <= keymap_count) {
      current_keymap = keymap;
      release_all();
    }
    return 0;
  }
  return 1;
}

int key_macro_bt_pair(int &keycode, keyevent_t &event) {
  if (!fn_mode) {
    digitalWrite(RSBT, LOW);
  }
  if (keycode == KEY_RSBT) {
    digitalWrite(RSBT, event.press ? HIGH : LOW);
    return 0;
  }
  return 1;
}

int key_macro_toggle_bt(int &keycode, keyevent_t &event) {
  if (event.press && keycode == KEY_TGBT) {
    bluetooth_driver_enabled = !bluetooth_driver_enabled;
    eeprom_write_byte((uint8_t *)BLUETOOTH_DRIVER_EEPROM, bluetooth_driver_enabled);
    return 0;
  }
  return 1;
}

int key_macro_toggle_usb(int &keycode, keyevent_t &event) {
  if (event.press && keycode == KEY_TUSB) {
    usb_driver_enabled = !usb_driver_enabled;
    eeprom_write_byte((uint8_t *)USB_DRIVER_EEPROM, usb_driver_enabled);
    return 0;
  }
  return 1;
}

int key_macro_reboot_program(int &keycode, keyevent_t &event) {
  if (event.press && keycode == KEY_RBPG) {
    _reboot_Teensyduino_();
    return 0;
  }
  return 1;
}

int key_macro_filter(int &keycode, keyevent_t &event) {
  return keycode < 0xC000;
}

void send_event(keyevent_t event) {
  int macro_propagation = 1;
  int keycode = keymaps[current_keymap][event.key.row][event.key.col];
  // Start Macros
  if (macro_propagation)
    macro_propagation = key_macro_fn(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_layer(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_bt_pair(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_toggle_bt(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_toggle_usb(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_reboot_program(keycode, event);
  if (macro_propagation)
    macro_propagation = key_macro_filter(keycode, event);
  // Send Normal Keys Signal
  if (macro_propagation) {
    if (event.press) {
      press_key(keycode);
    } else {
      release_key(keycode);
    }
  }
}
