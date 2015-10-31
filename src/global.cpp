#include "global.h"

matrix_row_t* matrix = new matrix_row_t[MATRIX_ROWS];
matrix_row_t* matrix_prev = new matrix_row_t[MATRIX_ROWS];

int usb_driver_enabled = eeprom_read_byte((uint8_t *)USB_DRIVER_EEPROM);
int bluetooth_driver_enabled = eeprom_read_byte((uint8_t *)BLUETOOTH_DRIVER_EEPROM);
