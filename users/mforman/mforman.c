#include "mforman.h"
#include <stdint.h>
#include "features/achordion.h"

userspace_config_t userspace_config;

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
    [NAV_DEL] = ACTION_TAP_DANCE_TAP_HOLD(KC_DEL, C(KC_DEL)),
    [MT_LPRN] = ACTION_TAP_DANCE_TAP_HOLD(KC_LPRN, KC_RCTL),
    [MT_RPRN] = ACTION_TAP_DANCE_TAP_HOLD(KC_RPRN, KC_LALT),
    [MT_EQL] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQL, KC_RSFT),
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
    if (!process_achordion(keycode, record)) {
        return false;
    }

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
        case TD(MT_LPRN):
        case TD(MT_RPRN):
        case TD(MT_EQL):
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

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    switch (other_keycode) {
        case TC_SPC:
        case TC_TAB:
        case TC_ENT:
            return true; // Homerow mods + thumb key
    }
    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case TC_SPC:
        case TC_TAB:
        case TC_ENT:
            return 0; // Bypass Achordion for thumb keys
    }

    return 800; // Otherwise use a timeout of 800 ms.
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
    achordion_task();
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
