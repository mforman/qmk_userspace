#include "mforman.h"

bool is_task_switch_active = false;
uint16_t task_switch_mod = KC_LGUI;

bool process_record_user_switcher(uint16_t keycode, keyrecord_t *record) {
    if (!super_task_switcher(
        &is_task_switch_active, task_switch_mod, KC_TAB, ALT_TAB,
        keycode, record
    )) {
        return false;
    }
    return true;
}

bool super_task_switcher(
    bool *active,
    uint16_t modkey,
    uint16_t switchkey,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
)  {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(modkey);
            }
            register_code(switchkey);
        } else {
            unregister_code(switchkey);
        }
        return false;
    } else if (*active) {
        switch (keycode) {
            // Leave command pressed to interact with
            // the task switcher
            case TC_BSP:
            case KC_LSFT:
            case KC_RIGHT ... KC_LEFT:
            case TC_TAB:
            case KC_TAB:
            case KC_Q:
            case KC_H:
                break;

            // Release command after up, down, escape
            // or anything not listed above
            case KC_DOWN ... KC_UP:
            case KC_ESCAPE:
            case KC_SPACE:
            case TC_SPC:
            case KC_ENTER:
            case TC_ENT:
                tap_code(keycode);
                unregister_code(modkey);
                *active = false;
                return false;
            default:
                return false;
        }
    }
    return true;
}
