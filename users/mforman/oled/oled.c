#include "mforman.h"

uint32_t oled_timer = 0;

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return rotation;
    } else {
        return OLED_ROTATION_270;
    }
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[]   = {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[]  = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    static const char PROGMEM mouse_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    if (layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if (layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else if (layer_state_is(_MOUSE)) {
        oled_write_P(mouse_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

#ifdef RGB_MATRIX_ENABLE
const char *rgb_matrix_anim_oled_text(uint8_t mode) {
    switch (mode) {
        case RGB_MATRIX_SOLID_COLOR:
            return PSTR("Solid");

#    ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
        case RGB_MATRIX_ALPHAS_MODS:
            return PSTR("Mods ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
        case RGB_MATRIX_GRADIENT_UP_DOWN:
            return PSTR("Grad ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_BAND_SAT
        case RGB_MATRIX_BAND_SAT:
            return PSTR("Band ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_TYPING_HEATMAP
        case RGB_MATRIX_TYPING_HEATMAP:
            return PSTR("Heat ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
        case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:
            return PSTR("Nexus");
#    endif

#    ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
        case RGB_MATRIX_SOLID_MULTISPLASH:
            return PSTR("Matrx");
#    endif

#    ifdef ENABLE_RGB_MATRIX_DIGITAL_RAIN
        case RGB_MATRIX_DIGITAL_RAIN:
            return PSTR("Rain ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_BREATHING
        case RGB_MATRIX_BREATHING:
            return PSTR("Pulse");
#    endif

#    ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
        case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
            return PSTR("Chvrn");
#    endif

#    ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
        case RGB_MATRIX_CYCLE_LEFT_RIGHT:
            return PSTR("Wave ");
#    endif

#    ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
        case RGB_MATRIX_DUAL_BEACON:
            return PSTR("Beacn");
#    endif

        default:
            return PSTR("Unkwn");
    }
}
#endif

void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   128, 128, 128, 0,   0,   0,  192, 224, 240, 240, 240, 240, 240, 240, 240, 224, 0,  0,  0,  0,  0,  0, 0, 0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0,  0,  0,  0,   0,   0,   0,   0,   0,   128, 192, 224, 240, 0,  0, 240, 252, 254, 255, 255, 255, 1,   240, 252, 255, 255, 255, 255, 255, 255, 255, 255, 127, 31,  7,   0, 0, 0, 0, 0, 0, 0, 0,
        240, 248, 252, 30, 14, 14, 14, 14, 14,  14,  30,  60, 56, 48, 0,  0,  240, 248, 252, 30,  14,  14,  14,  14,  14, 14,  30,  252, 248, 240, 0,   0,   254, 254, 252, 28, 14, 14, 14, 14, 0, 0, 254, 254, 252, 28, 14, 14, 14, 14, 30, 252, 248, 240, 0, 0, 240, 248, 252, 222, 206, 206, 206, 206, 206, 206, 222, 252, 248, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 255, 255, 255, 254, 240, 255, 255, 255, 255, 255, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 193, 128, 128, 128, 192, 240, 0, 0, 0, 0, 0, 0, 15, 31, 63, 120, 112, 112, 112, 112, 112, 112, 120, 60,  28,  12, 0, 0,   15,  31,  63,  120, 112, 112, 112, 112, 112, 112, 120, 63,  31,  15,  0,   0,   127, 127, 127, 0, 0, 0, 0, 0, 0, 0, 127,
        127, 127, 0,   0,  0,  0,  0,  0,  127, 127, 127, 0,  0,  15, 31, 63, 121, 113, 113, 113, 113, 113, 113, 121, 61, 29,  13,  0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0, 0, 0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   1,   3, 3, 3,   3,   1,   1,   3,   3,   7,   7,   7,   3,   3,   1,   3,   7,   7, 7, 7, 7, 7, 7, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    bool gui = modifiers & MOD_MASK_GUI;
    bool alt = modifiers & MOD_MASK_ALT;

    if (gui) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if (gui && alt) {
        oled_write_P(on_on_1, false);
    } else if (gui) {
        oled_write_P(on_off_1, false);
    } else if (alt) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (alt) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (gui) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (gui && alt) {
        oled_write_P(on_on_2, false);
    } else if (gui) {
        oled_write_P(on_off_2, false);
    } else if (alt) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (alt) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    bool ctrl  = modifiers & MOD_MASK_CTRL;
    bool shift = modifiers & MOD_MASK_SHIFT;

    if (ctrl) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if (ctrl && shift) {
        oled_write_P(on_on_1, false);
    } else if (ctrl) {
        oled_write_P(on_off_1, false);
    } else if (shift) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (shift) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (ctrl) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (ctrl && shift) {
        oled_write_P(on_on_2, false);
    } else if (ctrl) {
        oled_write_P(on_off_2, false);
    } else if (shift) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (shift) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_keylock_status(led_t led_usb_state) {
    if (led_usb_state.caps_lock) {
        oled_write_P(PSTR("CAPS "), false);
    } else if (is_caps_word_on()) {
        oled_write_P(PSTR("WORD "), false);
    } else {
        oled_write_P(PSTR("     "), false);
    }
}

void render_status_main(void) {
    render_space();
    render_layer_state();
    render_space();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
    render_space();
#ifdef RGB_MATRIX_ENABLE
    if (rgb_matrix_config.enable) {
        render_space();
        if (userspace_config.rgb_matrix_idle_anim) {
            oled_write_P(rgb_matrix_anim_oled_text(userspace_config.rgb_matrix_active_mode), false);
            oled_write_P(rgb_matrix_anim_oled_text(userspace_config.rgb_matrix_idle_mode), false);
        } else {
            oled_write_P(rgb_matrix_anim_oled_text(rgb_matrix_get_mode()), false);
        }
    } else {
        render_space();
        oled_write_P(PSTR(" Off "), false);
    }
#endif
    render_keylock_status(host_keyboard_led_state());
}

void render_status_secondary(void) {
    render_logo();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status_main();
    } else {
        render_status_secondary();
    }
    return false;
}
