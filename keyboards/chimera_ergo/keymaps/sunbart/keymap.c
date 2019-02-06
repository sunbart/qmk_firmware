#include QMK_KEYBOARD_H

enum chimera_ergo_layers
{
  _QWERTY,  // blue
  _SYMBOLS, // green
  _NAV,     // yellow
  _NUMPAD   // red
};

// Tap toggle defines
#define TT_SYMB TT(_SYMBOLS)
#define TT_NAV TT(_NAV)

// Goto layer defines
#define TO_BASE TO(_QWERTY)
#define TO_SYMB TO(_SYMBOLS)
#define TO_NAV TO(_NAV)

// Layer toggle defines
#define TG_NUM TG(_NUMPAD)

// Macro enum
enum custom_keycodes {
  M_BSDEL = SAFE_RANGE,
  M_SHIFT,
  M_FOLD,
  M_RMUP,
  M_RMDWN
};

// Keycode defines
#define SC_CAD LALT(LCTL(KC_DEL))
#define WIN_D LWIN(KC_D)
#define WIN_L LWIN(KC_L)
#define WIN_X LWIN(KC_X)
#define WIN_R LWIN(KC_R)
#define UNDENT LCTL(KC_LBRC)
#define INDENT LCTL(KC_RBRC)
#define LINEUP LCTL(LSFT(KC_UP))
#define LINEDWN LCTL(LSFT(KC_DOWN))

#define LONGPRESS_DELAY 150

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    M_BSDEL,
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
    M_SHIFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                         KC_SPC, TT_SYMB,       KC_SPC, TT_NAV
  ),

  [_SYMBOLS] = LAYOUT(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC,       KC_RBRC, KC_UNDS, KC_PLUS, KC_PIPE, KC_COLN, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_LCBR,       KC_RCBR, KC_MINS, KC_EQL,  KC_BSLS, KC_SCLN, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  SC_CAD,        TG_NUM,  KC_QUOT, KC_LABK, KC_RABK, KC_GRV,  _______,
                                        KC_LALT, TO_BASE,       _______, TO_NAV
  ),

  [_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       TG_NUM,  KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, _______,
    _______, KC_PSCR, WIN_D,   WIN_X,   WIN_L,   KC_CAPS,       LINEUP,  KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, _______,
    _______, KC_A,    KC_S,    WIN_R,   KC_LWIN, KC_NLCK,       LINEDWN, UNDENT,  KC_UP,   INDENT,  M_RMUP,  KC_F5,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_SLCK,       M_FOLD,  KC_LEFT, KC_DOWN, KC_RGHT, M_RMDWN, _______,
                                        _______, TO_SYMB,       _______, TO_BASE
  ),

  [_NUMPAD] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       TG_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, TO_BASE, XXXXXXX,       KC_PEQL, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_UNDS, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, TO_BASE,
    KC_RCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_PERC, KC_P0,   KC_PCMM, KC_PDOT, KC_PPLS, _______,
                                        _______, TO_SYMB,       _______, TO_NAV
  ),
};

// Tracking vars for macros
static bool m_shift_status = false;
static bool m_bsdel_was_shifted = false;

// Macros and stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_SHIFT: // Track the actual state of the Shift key
      if (record->event.pressed) {
        m_shift_status = true;
        register_code(KC_LSFT);
      }
      else {
        m_shift_status = false;
        unregister_code(KC_LSFT);
      }
      return false;
    case M_BSDEL: // Send Backspace or Delete if shifted
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          m_bsdel_was_shifted = true;
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
        }
        else {
          m_bsdel_was_shifted = false;
          register_code(KC_BSPACE);
        }
      }
      else {
        if (m_bsdel_was_shifted) {
          unregister_code(KC_DEL);
          if (m_shift_status) {
            register_code(KC_LSFT);
          }
        }
        else {
          unregister_code(KC_BSPACE);
        }
      }
      return false;
    case M_FOLD:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("ko"));
      }
      return false;
    case M_RMUP:
      if (record->event.pressed) {
        register_code(KC_MS_BTN2);
        register_code(KC_MS_WH_UP);
      }
      else {
        unregister_code(KC_MS_WH_UP);
        unregister_code(KC_MS_BTN2);
      }
      return false;
    case M_RMDWN:
      if (record->event.pressed) {
        register_code(KC_MS_BTN2);
        register_code(KC_MS_WH_DOWN);
      }
      else {
        unregister_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_BTN2);
      }
      return false;
  }
  return true;
};

// Switch LED color according to the current layer
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case _QWERTY:
      set_led_blue;
      break;
    case _NUMPAD:
      set_led_red;
      break;
    case _SYMBOLS:
      set_led_green;
      break;
    case _NAV:
      set_led_yellow;
      break;
    default:
      set_led_magenta;
      break;
  }
};