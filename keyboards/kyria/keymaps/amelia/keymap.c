/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// todo
// wasd -> arrows
// wasd raise -> page up/down home/end
// hold enter -> shift

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};



/**
 * Cool Function where a single key does ALT+TAB
 * From: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 */
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

enum custom_keycodes {            // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  UNDO,
  REDO,
  MAIL,
  STACK,
  SLACK,
  CHROME,
  LINEAR,
  NOTES,
  SPOTIFY,
  ZOOM,
  TEXT_EDITOR
};

// key processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LCMD);
        }
        alt_tab_timer = timer_read();
          register_code(KC_LCMD);
        register_code(KC_TAB);
      } else {
          unregister_code(KC_LCMD);
        unregister_code(KC_TAB);
      }
      break;
    case UNDO:
      if (record->event.pressed) {
        register_code(KC_LCMD);
        register_code(KC_Z);
      } else {
        unregister_code(KC_LCMD);
        unregister_code(KC_Z);
      }
      break;
    case REDO:
      if (record->event.pressed) {
        register_code(KC_LCMD);
        register_code(KC_LSHIFT);
        register_code(KC_Z);
      } else {
        unregister_code(KC_LCMD);
        unregister_code(KC_LSHIFT);
        unregister_code(KC_Z);
      }
      break;
    case MAIL:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_1);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_1);
      }
      break;
    case STACK:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_2);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_2);
      }
      break;
    case LINEAR:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_3);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_3);
      }
      break;
    case CHROME:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_Q);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_Q);
      }
      break;
    case TEXT_EDITOR:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_W);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_W);
      }
      break;
    case SLACK:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_E);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_E);
      }
      break;
    case NOTES:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_A);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_A);
      }
      break;
    case SPOTIFY:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_S);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_S);
      }
      break;
    case ZOOM:
      if (record->event.pressed) {
        register_code(KC_LOPT);
        register_code(KC_D);
      } else {
        unregister_code(KC_LOPT);
        unregister_code(KC_D);
      }
      break;
  }
  return true;
}

// The very important timer.
void matrix_scan_user(void) {
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 300) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
  }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |LShift/BS | A  |   S  |  D   |   F  |   G   |                             |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | Ctrl/` |   Z  |   X  |   C  |   V  |   B  |alt+tab| undo|  |KC_PGUP|KC_PGDN|  N |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Ctrl | Opt  | GUI  | Space| Alt  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      LT(_RAISE, KC_ESC), KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      KC_LSHIFT,          KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      LCTL_T(KC_GRV),     KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   ALT_TAB,   UNDO, KC_PGUP, KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LCTL, KC_LOPT, KC_LGUI, LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), LT(_LOWER, KC_ENT), LT(_RAISE, KC_SPC), KC_LALT,  KC_BSPC, KC_RALT
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, _______, _______, _______, _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL,  KC_SCLN, _______, _______, _______
    ),
/*quRaise Layer: Number keys, media, navigation
 *qu,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | MAIL | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, STACK,   SLACK,  CHROME, TEXT_EDITOR, KC_VOLU,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______,  MAIL, KC_MPRV, KC_MPLY, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

// static void render_kyria_logo(void) {
//     static const char PROGMEM kyria_logo[] = {
//         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
//         0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
//         0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
//     };
//     oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
// }

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    // if (!is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
            oled_write_P(PSTR("Default\n"), false);

    // } else {
        // render_kyria_logo();
    // }
}
#endif

uint8_t mod_state;
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    mod_state = get_mods();

    if (index == 0) {
        // Volume control
        if (clockwise) {
            register_code(KC_LCMD);
            register_code(KC_Z);
            unregister_code(KC_LCMD);
            unregister_code(KC_Z);
            // tap_code(UNDO);
        } else {
            register_code(KC_LCMD);
            register_code(KC_LSHIFT);
            register_code(KC_Z);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSHIFT);
            unregister_code(KC_Z);
            // tap_code(REDO);
        }
    }
    else if (index == 1) {
        if (get_mods() & MOD_MASK_ALT) {
            del_mods(MOD_MASK_ALT);
            if (clockwise) {
                register_code(KC_LOPT);
                tap_code(KC_LEFT);
                unregister_code(KC_LOPT);
            } else {
                register_code(KC_LOPT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LOPT);
            }
            set_mods(mod_state);
        } else if (get_mods() & MOD_MASK_GUI) {
            del_mods(MOD_MASK_GUI);
            if (clockwise) {
                tap_code(KC_LEFT);
            } else {
                tap_code(KC_RIGHT);
            }
            set_mods(mod_state);
        } else if (biton32(layer_state) == 2) {
            if (clockwise) {
                // tap_code(KC_PGUP);
                // tap_code(KC_WH_U);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
            } else {
                // tap_code(KC_PGDN);
                // tap_code(KC_WH_D);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
            }
        } else if (biton32(layer_state) == 1) {
            if (clockwise) {
                register_code(KC_LSHIFT);
                register_code(KC_LCTL);
                tap_code(KC_RIGHT);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LCTL);
            } else {
                register_code(KC_LSHIFT);
                register_code(KC_LCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LCTL);
            }
        } else {
            if (clockwise) {
                tap_code(KC_UP);
            } else {
                tap_code(KC_DOWN);
            }
        }
    }
}
#endif
