#pragma once

bool process_record_user_switcher(uint16_t keycode, keyrecord_t *record);
bool super_task_switcher(
    bool *active,
    uint16_t modkey,
    uint16_t switchkey,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);

extern uint16_t task_switch_mod;
