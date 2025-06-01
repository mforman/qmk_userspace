#include "mforman.h"
#include <stdint.h>

userspace_config_t userspace_config;

#ifdef COMBO_ENABLE
// COLEMAK
const uint16_t PROGMEM wfEsc[]      = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM wpMouse[]    = {KC_W, KC_P, COMBO_END};
const uint16_t PROGMEM rsBspc[]     = {MT_R, MT_S, COMBO_END};
const uint16_t PROGMEM arsBspc[]    = {MT_A, MT_R, MT_S, COMBO_END};
const uint16_t PROGMEM stTab[]      = {MT_S, MT_T, COMBO_END};
const uint16_t PROGMEM luBckSlsh[]  = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM neDash[]     = {MT_N, MT_E, COMBO_END};
const uint16_t PROGMEM eiColon[]    = {MT_E, MT_I, COMBO_END};
const uint16_t PROGMEM hCommUnd[]   = {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM commDotScl[] = {KC_DOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM xcCopy[]     = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM xdCut[]      = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM cdPaste[]    = {KC_C, KC_D, COMBO_END};

// Others
const uint16_t PROGMEM volDwnUp[]    = {KC_VOLD, KC_VOLU, COMBO_END};
const uint16_t PROGMEM spcTabCmdCt[] = {TC_SPC, TC_TAB, COMBO_END};
const uint16_t PROGMEM grvSft[]      = {KC_GRV, KC_RCTL, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    COMBO(wfEsc, KC_ESC),
    COMBO(wpMouse, TG(_MOUSE)),
    COMBO(rsBspc, KC_BSPC),
    COMBO(arsBspc, BSP_WRD),
    COMBO(stTab, KC_TAB),
    COMBO(luBckSlsh, KC_BSLS),
    COMBO(neDash, KC_MINS),
    COMBO(eiColon, KC_COLN),
    COMBO(hCommUnd, KC_UNDS),
    COMBO(commDotScl, KC_SCLN),
    COMBO(xcCopy, LCTL(KC_C)),
    COMBO(xdCut, LCTL(KC_X)),
    COMBO(cdPaste, LCTL(KC_V)),

    COMBO(volDwnUp, KC_MUTE),
    COMBO(spcTabCmdCt, LCTL(KC_LGUI)),
    COMBO(grvSft, CMD_GRV)
};
// clang-format on
#endif

#ifdef TAP_DANCE_ENABLE
// clang-format off
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [NAV_UP] = ACTION_TAP_DANCE_TAP_HOLD(KC_UP, C(KC_HOME)),
    [NAV_DOWN] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOWN, C(KC_END)),
    [NAV_LEFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_LEFT, KC_HOME),
    [NAV_RGHT] = ACTION_TAP_DANCE_TAP_HOLD(KC_RGHT, KC_END),
    [NAV_BSPC] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, C(KC_BSPC)),
    [NAV_DEL] = ACTION_TAP_DANCE_TAP_HOLD(KC_DEL, C(KC_DEL))
};
// clang-format on
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    process_record_user_oled(keycode, record);
#endif
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

#ifdef SWITCHER_ENABLE
    if (!process_record_user_switcher(keycode, record)) {
        return false;
    }
#endif

    tap_dance_action_t *action;

    switch (keycode) {
        case TD(NAV_UP):
        case TD(NAV_DOWN):
        case TD(NAV_LEFT):
        case TD(NAV_RGHT):
        case TD(NAV_BSPC):
        case TD(NAV_DEL):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        default:
            return true;
    }
    return true;
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
#ifdef OLED_ENABLE
    oled_off();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
    suspend_power_down_keymap();
}

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
#ifdef OLED_ENABLE
    oled_on();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
    suspend_wakeup_init_keymap();
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
}

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}
__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = false;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return layer_state_set_keymap(state);
};
