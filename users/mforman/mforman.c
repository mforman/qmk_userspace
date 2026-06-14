#include "mforman.h"
#include <stdint.h>
#include "g/keymap_combo.h"

static bool     last_alpha_valid   = false;
static uint16_t last_alpha_time    = 0;
static uint16_t last_alpha_keycode = KC_NO;

#ifdef TAP_DANCE_ENABLE
// clang-format off
static uint16_t word_mod_key(uint16_t kc) {
    return keymap_config.swap_lctl_lgui ? C(kc) : A(kc);
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            uint16_t kc = tap_hold->hold;
            if (tap_hold->tap == KC_BSPC && kc == KC_NO) {
                kc = word_mod_key(KC_BSPC);
            } else if (tap_hold->tap == KC_DEL && kc == KC_NO) {
                kc = word_mod_key(KC_DEL);
            } else if (kc == KC_HOME || kc == KC_END) {
                uint8_t saved_mods = get_mods() & MOD_MASK_CTRL;
                del_mods(MOD_MASK_CTRL);
                register_code16(kc);
                add_mods(saved_mods);
                tap_hold->held = kc;
                return;
            }
            register_code16(kc);
            tap_hold->held = kc;
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
    [NAV_UP] = ACTION_TAP_DANCE_TAP_HOLD(KC_UP, G(KC_HOME)),
    [NAV_DOWN] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOWN, G(KC_END)),
    [NAV_LEFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_LEFT, KC_HOME),
    [NAV_RGHT] = ACTION_TAP_DANCE_TAP_HOLD(KC_RGHT, KC_END),
    [NAV_BSPC] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, KC_NO),
    [NAV_DEL] = ACTION_TAP_DANCE_TAP_HOLD(KC_DEL, KC_NO)
};
// clang-format on
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    process_record_user_oled(keycode, record);
#endif
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    // Track last alpha for magic-shift repeat logic.
    // Exclude MAGIC_SHIFT itself so its initial press (tap.count=0, tap_kc=KC_F24)
    // doesn't clobber the context before the tap fires.
    if (record->event.pressed && keycode != MAGIC_SHIFT) {
        uint16_t tap_kc = get_tap_keycode(keycode);
        if (tap_kc >= KC_A && tap_kc <= KC_Z) {
            last_alpha_keycode = tap_kc;
            last_alpha_time    = record->event.time;
            last_alpha_valid   = true;
        } else if (tap_kc > KC_TRANSPARENT && tap_kc < 0x100) {
            last_alpha_valid = false;
        }
    }

    switch (keycode) {
        case BSP_WRD:
            if (record->event.pressed) {
                tap_code16(word_mod_key(KC_BSPC));
            }
            return false;

        case MAGIC_SHIFT:
            if (record->tap.count && record->event.pressed) {
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    clear_oneshot_mods();
                    caps_word_on();
                } else if (last_alpha_valid && timer_elapsed(last_alpha_time) < 1200) {
                    tap_code16(last_alpha_keycode);
                } else {
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                }
                return false;
            }
            return true;

        case TD(NAV_UP):
        case TD(NAV_DOWN):
        case TD(NAV_LEFT):
        case TD(NAV_RGHT):
        case TD(NAV_BSPC):
        case TD(NAV_DEL): {
            uint8_t           td_idx   = QK_TAP_DANCE_GET_INDEX(keycode);
            tap_dance_state_t *td_state = tap_dance_get_state(td_idx);
            if (!record->event.pressed && td_state->count && !td_state->finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)tap_dance_actions[td_idx].user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
        }
        default:
            return true;
    }
    return true;
}

