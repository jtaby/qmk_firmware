#include QMK_KEYBOARD_H

enum layers {
    _ALPHA,
    _NUMPAD,
    _NAVIGATION,
    _SHIFT_NUMPAD
};

enum custom_keycodes {
    APP_FWD = SAFE_RANGE,
    APP_BACK
};

#define HRM_A LSFT_T(KC_A)
#define HRM_S LCTL_T(KC_S)
#define HRM_D LALT_T(KC_D)
#define HRM_F LGUI_T(KC_F)
#define HRM_J RGUI_T(KC_J)
#define HRM_K RALT_T(KC_K)
#define HRM_L RCTL_T(KC_L)
#define HRM_SCLN RSFT_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,
        HRM_A,   HRM_S,  HRM_D,  HRM_F,  KC_G,       KC_H,    HRM_J,   HRM_K,     HRM_L,    HRM_SCLN,
        KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,
                         KC_SPC,  MO(_NUMPAD),        MO(_NAVIGATION), KC_ENT
    ),

    [_NUMPAD] = LAYOUT_split_3x5_2(
        KC_ESC,  _______, _______, _______, KC_BSPC,   KC_PAST, KC_P7,   KC_P8,    KC_P9,    KC_PMNS,
        _______, _______, APP_BACK, APP_FWD, KC_ENT,   KC_PSLS, KC_P4,   KC_P5,    KC_P6,    KC_PPLS,
        _______, _______, _______, _______, _______,   KC_P0,   KC_P1,   KC_P2,    KC_P3,    KC_PDOT,
                         _______, _______,            _______, _______
    ),

    [_NAVIGATION] = LAYOUT_split_3x5_2(
        KC_ESC,  KC_LPRN, KC_RPRN, KC_UNDS, KC_BSLS,   _______, _______, _______,   _______,  _______,
        KC_TILD, KC_LCBR, KC_RCBR, KC_MINS, KC_QUOT,   KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT,  LCA(KC_LSFT),
        KC_PIPE, KC_LBRC, KC_RBRC, KC_EQL,  KC_TAB,    KC_PGDN, _______, _______,   _______,  _______,
                          KC_BSPC, _______,            _______, _______
    ),

    [_SHIFT_NUMPAD] = LAYOUT_split_3x5_2(
        _______, _______, _______, _______, _______,   _______, KC_AMPR, KC_ASTR, KC_LPRN, _______,
        _______, _______, _______, _______, _______,   _______, KC_DLR,  KC_PERC, KC_CIRC, _______,
        _______, _______, _______, _______, _______,   KC_RPRN, KC_EXLM, KC_AT,   KC_HASH, _______,
                          _______, _______,            _______, _______
    )
};

static bool app_switcher_active = false;

static void release_app_switcher(void) {
    if (app_switcher_active) {
        unregister_code(KC_LGUI);
        app_switcher_active = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case APP_FWD:
            if (record->event.pressed) {
                if (!app_switcher_active) {
                    register_code(KC_LGUI);
                    app_switcher_active = true;
                }
                tap_code(KC_TAB);
            }
            return false;

        case APP_BACK:
            if (record->event.pressed) {
                if (!app_switcher_active) {
                    register_code(KC_LGUI);
                    app_switcher_active = true;
                }
                tap_code16(S(KC_TAB));
            }
            return false;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUMPAD, _NAVIGATION, _SHIFT_NUMPAD);

    if (!layer_state_cmp(state, _NUMPAD) && !layer_state_cmp(state, _NAVIGATION)) {
        release_app_switcher();
    }

    return state;
}

static bool is_home_row_hrm(uint16_t keycode) {
    switch (keycode) {
        case HRM_A:
        case HRM_S:
        case HRM_D:
        case HRM_F:
        case HRM_J:
        case HRM_K:
        case HRM_L:
        case HRM_SCLN:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;

    if (is_home_row_hrm(keycode)) {
        return TAPPING_TERM;
    }

    return TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;

    if (is_home_row_hrm(keycode)) {
        return QUICK_TAP_TERM;
    }

    return QUICK_TAP_TERM;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    (void)record;

    return is_home_row_hrm(keycode);
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    (void)record;

    switch (keycode) {
        case HRM_F:
        case HRM_J:
            return false;
        default:
            break;
    }

    return is_home_row_hrm(keycode);
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    (void)record;

    if (is_home_row_hrm(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }

    return 0;
}
