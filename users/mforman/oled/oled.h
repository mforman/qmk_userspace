#pragma once

#include "quantum.h"
#include "oled_driver.h"

extern uint32_t oled_timer;

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);

void render_layout_name(void);
void render_layer_state(void);
void render_logo(void);
void render_space(void);
void render_mod_status_gui_alt(uint8_t modifiers);
void render_mod_status_ctrl_shift(uint8_t modifiers);
void render_os_config(void);
void render_status_main(void);
void render_status_secondary(void);

#ifdef RGB_MATRIX_ENABLE
const char *rgb_matrix_anim_oled_text(uint8_t mode);
#endif
