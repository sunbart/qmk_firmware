// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
//#include <print.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum chimera_ergo_layers
{
  _QWERTY,  // normal
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

// Macro defines
#define M_BSDEL M(0)
#define M_SPUND M(1)
#define M_SPIND M(2)

// Keycode defines
#define SC_CAD LALT(LCTL(KC_DEL))
#define WIN_D LWIN(KC_D)
#define WIN_L LWIN(KC_L)
#define WIN_X LWIN(KC_X)

// #define TAPPING_TERM 200
// #define TAPPING_TOGGLE 2
#define LONGPRESS_DELAY 150
//#define LAYER_TOGGLE_DELAY 300

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    M_BSDEL,
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_F5,
    KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                        TT_SYMB, M_SPUND,       M_SPIND, TT_NAV
  ),

  [_SYMBOLS] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       TG_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC,       KC_RBRC, KC_UNDS, KC_PLUS, KC_PIPE, KC_TILD, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_LCBR,       KC_RCBR, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LABK,       KC_RABK, KC_QUOT, KC_DQT,  XXXXXXX, XXXXXXX, _______,
                                        TO_BASE, _______,       _______, TO_NAV
  ),

  [_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       TG_NUM,  KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, _______,
    _______, KC_PSCR, WIN_D,   WIN_X,   WIN_L,   KC_CAPS,       XXXXXXX, KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, SC_CAD,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_LWIN, KC_NLCK,       XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MYCM, KC_SLCK,       XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
                                        TO_SYMB, _______,       _______, TO_BASE
  ),

  [_NUMPAD] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       TG_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, TO_BASE, XXXXXXX,       KC_PEQL, KC_P4,   KC_P5,   KC_P6,   KC_PAST, TO_BASE,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_UNDS, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_PERC, KC_P0,   KC_PCMM, KC_PDOT, KC_PPLS, _______,
                                        TO_SYMB, _______,       _______, TO_NAV
  ),

};


const uint16_t PROGMEM fn_actions[] = {

};

// Tracks vars for macros
static bool m_bsdel_was_shifted = false;
static bool m_spund_was_shifted = false;
static bool m_spind_was_shifted = false;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case 0: // Send Backspace or Delete if shifted
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
          register_code(KC_LSFT);
        }
        else {
          unregister_code(KC_BSPACE);
        }
      }
    break;
    case 1: // Send Space or CTRL+[ if shifted (unident in Sublime)
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          m_spund_was_shifted = true;
          unregister_code(KC_LSFT);
          register_code(KC_LCTRL);
          register_code(KC_LBRACKET);
        }
        else {
          m_spund_was_shifted = false;
          register_code(KC_SPACE);
        }
      }
      else {
        if (m_spund_was_shifted) {
          unregister_code(KC_LBRACKET);
          unregister_code(KC_LCTRL);
          register_code(KC_LSFT);
        }
        else {
          unregister_code(KC_SPACE);
        }
      }
    break;
    case 2: // Send Space or CTRL+] if shifted (ident in Sublime)
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          m_spind_was_shifted = true;
          unregister_code(KC_LSFT);
          register_code(KC_LCTRL);
          register_code(KC_RBRACKET);
        }
        else {
          m_spind_was_shifted = false;
          register_code(KC_SPACE);
        }
      }
      else {
        if (m_spind_was_shifted) {
          unregister_code(KC_RBRACKET);
          unregister_code(KC_LCTRL);
          register_code(KC_LSFT);
        }
        else {
          unregister_code(KC_SPACE);
        }
      }
    break;
  }
  return MACRO_NONE;
};


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
