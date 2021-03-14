
/**
 * Cool Function where a single key does ALT+TAB
 * From: https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
 */
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

enum custom_keycodes {            // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  UNDO,
  REDO
};

// key processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case UNDO:
      if (record->event.pressed) {
          register_code(KC_LCTL);
        register_code(KC_Z);
      } else {
        unregister_code(KC_LCTL);
        unregister_code(KC_Z);
      }
      break;
    case REDO:
      if (record->event.pressed) {
          register_code(KC_LCTL);
          register_code(KC_LSHIFT);
        register_code(KC_Z);
      } else {
        unregister_code(KC_LCTL);
        unregister_code(KC_LSHIFT);
        unregister_code(KC_Z);
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
