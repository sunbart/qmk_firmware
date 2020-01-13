#include QMK_KEYBOARD_H

// Macro enum
enum custom_keycodes {
  M_P0 = SAFE_RANGE,
  M_P00,
  M_PDOT,
  M_P1,
  M_P2,
  M_P3,
  M_P4,
  M_P5,
  M_P6,
  M_P7,
  M_P8,
  M_P9
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0, default layer
 ___________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |  BACK  |
|  ESC   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   |  F13   |  F14   |  F15   |  F16   | DELETE |  SPACE |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|   `    |        |        |        |        |        |        |        |        |        |        |   -    |   +    |  BACK  |  BACK  |  NUM   |        |        |        |
|   ~    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   _    |   =    |  SPACE |  SPACE |  LOCK  |   /    |   *    |   -    |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|            |        |        |        |        |        |        |        |        |        |        |   [    |   ]    |      \      |   7    |   8    |   9    |        |
|    TAB     |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |   {    |   }    |      |      | INSERT |  HOME  | PG UP  |   +    |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|_____________|________|________|________|________|
|              |        |        |        |        |        |        |        |        |        |   ;    |   '    |                    |   4    |   5    |   6    |        |
|   CAPS LOCK  |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   :    |   "    |       ENTER        | DELETE |  END   | PG DN  |   +    |
|______________|________|________|________|________|________|________|________|________|________|________|________|____________________|________|________|________|________|
|         |        |        |        |        |        |        |        |        |   ,    |   .    |   /    |        |                |   1    |   2    |   3    |        |
| lSHIFT  | LSHIFT |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   <    |   >    |   ?    | RSHIFT |     RSHIFT     |        |   ↑    |        | ENTER  |
|_________|________|________|________|________|________|________|________|________|________|________|________|________|________________|________|________|________|________|
|          |          |          |                                                        |        |        |        |        |        |   0    |   00   |   .    |        |
|  LCTRL   |   LGUI   |   LALT   |                         SPACE                          |  RALT  |  RGUI  |  RGUI  |  APP   | RCTRL  |   ←    |   ↓    |   →    | ENTER  |
|__________|__________|__________|________________________________________________________|________|________|________|________|________|________|________|________|________|
*/
  LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,    KC_F15,  KC_F16,  KC_DEL,  KC_BSPC,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,   M_P7,    M_P8,    M_P9,    KC_PPLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,    M_P4,    M_P5,    M_P6,    KC_PPLS,
    KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_RSFT,   M_P1,    M_P2,    M_P3,    KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_RGUI, KC_APP,  KC_RCTL,   M_P0,    M_P00,   M_PDOT,  KC_PENT),
};

bool numlock_on(void) {
  return host_keyboard_leds() & (1 << USB_LED_NUM_LOCK);
};

// Macros and stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_P0:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P0);
        }
        else {
          register_code(KC_LEFT);
        }
      }
      else {
        unregister_code(KC_P0);
        unregister_code(KC_LEFT);
      }
      return false;
    case M_P00:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P0);
          unregister_code(KC_P0);
          register_code(KC_P0);
        }
        else {
          register_code(KC_DOWN);
        }
      }
      else {
        unregister_code(KC_P0);
        unregister_code(KC_DOWN);
      }
      return false;
    case M_PDOT:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_PDOT);
        }
        else {
          register_code(KC_RIGHT);
        }
      }
      else {
        unregister_code(KC_PDOT);
        unregister_code(KC_RIGHT);
      }
      return false;
    case M_P1:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P1);
        }
      }
      else {
        unregister_code(KC_P1);
      }
      return false;
    case M_P2:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P2);
        }
        else {
          register_code(KC_UP);
        }
      }
      else {
        unregister_code(KC_P2);
        unregister_code(KC_UP);
      }
      return false;
    case M_P3:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P3);
        }
      }
      else {
        unregister_code(KC_P3);
      }
      return false;
    case M_P4:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P4);
        }
        else {
          register_code(KC_DELETE);
        }
      }
      else {
        unregister_code(KC_P4);
        unregister_code(KC_DELETE);
      }
      return false;
    case M_P5:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P5);
        }
        else {
          register_code(KC_END);
        }
      }
      else {
        unregister_code(KC_P5);
        unregister_code(KC_END);
      }
      return false;
    case M_P6:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P6);
        }
        else {
          register_code(KC_PGDOWN);
        }
      }
      else {
        unregister_code(KC_P6);
        unregister_code(KC_PGDOWN);
      }
      return false;
    case M_P7:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P7);
        }
        else {
          register_code(KC_INSERT);
        }
      }
      else {
        unregister_code(KC_P7);
        unregister_code(KC_INSERT);
      }
      return false;
    case M_P8:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P8);
        }
        else {
          register_code(KC_HOME);
        }
      }
      else {
        unregister_code(KC_P8);
        unregister_code(KC_HOME);
      }
      return false;
    case M_P9:
      if (record->event.pressed) {
        if (numlock_on()) {
          register_code(KC_P9);
        }
        else {
          register_code(KC_PGUP);
        }
      }
      else {
        unregister_code(KC_P9);
        unregister_code(KC_PGUP);
      }
      return false;
  };
  return true;
};

