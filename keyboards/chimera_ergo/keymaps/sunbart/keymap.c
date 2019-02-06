#include QMK_KEYBOARD_H

#define LONGPRESS_DELAY 150

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum chimera_ergo_layers
{
  QWERTY,  // LED: blue
  SYMBOLS, // LED: green
  NAV,     // LED: yellow
  NUMPAD   // LED: red
};

// Tap Toggle defines
#define TT_SYMB TT(SYMBOLS)
#define TT_NAV TT(NAV)

// Goto Layer defines
#define TO_BASE TO(QWERTY)
#define TO_SYMB TO(SYMBOLS)
#define TO_NAV TO(NAV)

// Layer Toggle defines
#define TG_NUM TG(NUMPAD)

// Macro enum
enum custom_keycodes {
  M_BSDEL = SAFE_RANGE, // Track the actual state of the Shift key
  M_SHIFT, // Send Backspace or Delete if shifted
  M_FUFLD, // Sublime 3 Fold/Unfold (no shift/shift)
  M_RMUP, // Sublime 3 switch to tab to the left
  M_RMDWN, // Sublime 3 switch to tab to the right
  M_FOLD1, // Sublime 3 Fold indent level 1
  M_FOLD2, // Sublime 3 Fold indent level 2
  M_FOLD3, // Sublime 3 Fold indent level 3
  M_FOLD4, // Sublime 3 Fold indent level 4
  M_UFALL, // Sublime 3 Unfold All
  M_SIDBR, // Sublime 3 toggle Side Bar
  M_COLSW // Sublime 3 toggle editor column count
};

// Keycode defines
#define SC_CAD LALT(LCTL(KC_DEL)) // Ctrl+Alt+Delete
#define WIN_D LWIN(KC_D) // Win+D - Show Windows desktop
#define WIN_L LWIN(KC_L) // Win+L - Lock the PC
#define WIN_X LWIN(KC_X) // Win+X - Open the Windows Quick Access Menu
#define WIN_R LWIN(KC_R) // Win+R - Open the Run dialog
#define UNDENT LCTL(KC_LBRC) // Sublime 3 Unindent selection
#define INDENT LCTL(KC_RBRC) // Sublime 3 Indent selection
#define LINEUP LCTL(LSFT(KC_UP)) // Sublime 3 Move selection Up
#define LINEDWN LCTL(LSFT(KC_DOWN)) // Sublime 3 Moce selection Down

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT(
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    M_BSDEL,
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
    M_SHIFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                         KC_SPC, TT_SYMB,       KC_SPC, TT_NAV
  ),

  [SYMBOLS] = LAYOUT(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC,       KC_RBRC, KC_UNDS, KC_PLUS, KC_PIPE, KC_COLN, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_LCBR,       KC_RCBR, KC_MINS, KC_EQL,  KC_BSLS, KC_SCLN, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  SC_CAD,        TG_NUM,  KC_QUOT, KC_LABK, KC_RABK, KC_GRV,  _______,
                                        KC_LALT, TO_BASE,       _______, TO_NAV
  ),

  [NAV] = LAYOUT(
    _______, M_FOLD1, M_FOLD2, M_FOLD3, M_FOLD4, M_UFALL,       TG_NUM,  KC_INS,  KC_HOME, KC_PGUP, M_COLSW, _______,
    _______, KC_PSCR, WIN_D,   WIN_X,   WIN_L,   KC_CAPS,       LINEUP,  KC_DEL,  KC_END,  KC_PGDN, M_SIDBR, _______,
    _______, KC_A,    KC_S,    WIN_R,   KC_LWIN, KC_NLCK,       LINEDWN, UNDENT,  KC_UP,   INDENT,  M_RMUP,  KC_F5,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_SLCK,       M_FUFLD, KC_LEFT, KC_DOWN, KC_RGHT, M_RMDWN, _______,
                                        _______, TO_SYMB,       _______, TO_BASE
  ),

  [NUMPAD] = LAYOUT(
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
static bool m_colsw_state = false;

// Macros and stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  // Track the actual state of the Shift key
    case M_SHIFT:
      if (record->event.pressed) {
        m_shift_status = true;
        register_code(KC_LSFT);
      }
      else {
        m_shift_status = false;
        unregister_code(KC_LSFT);
      }
      return false;
    // Send Backspace or Delete if shifted
    case M_BSDEL:
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
    // Sublime 3 Fold/Unfold (no shift/shift)
    case M_FUFLD:
      if (record->event.pressed) {
        if (m_shift_status == false) {
            SEND_STRING(SS_LCTRL("{"));
        }
        else {
            SEND_STRING(SS_LCTRL("}"));
        }
      }
      return false;
    // Sublime 3 switch to tab to the left
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
    // Sublime 3 switch to tab to the right
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
    // Sublime 3 Fold indent level 1
    case M_FOLD1:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("k1"));
      }
      return false;
    // Sublime 3 Fold indent level 2
    case M_FOLD2:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("k2"));
      }
      return false;
    // Sublime 3 Fold indent level 3
    case M_FOLD3:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("k3"));
      }
      return false;
    // Sublime 3 Fold indent level 4
    case M_FOLD4:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("k4"));
      }
      return false;
    // Sublime 3 Unfold All
    case M_UFALL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("kj"));
      }
      return false;
    // Sublime 3 toggle Side Bar
    case M_SIDBR:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("kb"));
      }
      return false;
    // Sublime 3 toggle editor column count
    case M_COLSW:
      if (record->event.pressed) {
        if (m_colsw_state) {
          SEND_STRING(SS_LSFT(SS_LALT("1")));
        }
        else {
          SEND_STRING(SS_LSFT(SS_LALT("2")));
        }
        m_colsw_state = !m_colsw_state;
      }
      return false;
  }
  return true;
};

// Switch LED color according to the current layer
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case QWERTY:
      set_led_blue;
      break;
    case SYMBOLS:
      set_led_green;
      break;
    case NAV:
      set_led_yellow;
      break;
    case NUMPAD:
      set_led_red;
      break;
    default:
      set_led_magenta;
      break;
  }
};