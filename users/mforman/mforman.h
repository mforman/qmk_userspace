#pragma once

#include QMK_KEYBOARD_H

#include "eeprom.h"
#include "version.h"

#ifdef SWITCHER_ENABLE
#    include "switcher/switcher.h"
#endif
#ifdef OLED_DRIVER_ENABLE
#    include "oled/oled.h"
#endif

// clang-format off
enum keyboard_layers {
    _COLEMAK = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE };

enum mforman_keycodes {
    RGB_IDL,
    KC_RGB_T,
    RGBRST };

enum tap_dances {
    NAV_UP,
    NAV_DOWN,
    NAV_LEFT,
    NAV_RGHT,
    NAV_BSPC,
    NAV_DEL,
    MT_LPRN,
    MT_RPRN,
    MT_EQL };
// clang-format on

// Thumb cluster keys
#define TC_GUI OSM(MOD_LGUI)
#define TC_SPC LCTL_T(KC_SPACE)
#define TC_TAB LT(_LOWER, KC_TAB)
#define TC_OPT OSM(MOD_LALT)
#define TC_BSP LSFT_T(KC_BSPC)
#define TC_ENT LT(_RAISE, KC_ENTER)

// Home row modifiers.
// GASC/ ◆⎇ ⇧⎈
// CG_TOGG will switch it to the CASG in MacOS
// Leave shift on the thumb on the alpha layer
// https://precondition.github.io/home-row-mods#gasc

// Left-hand home row mods
#define MT_A LGUI_T(KC_A)
#define MT_R LALT_T(KC_R)
#define MT_S LSFT_T(KC_S)
#define MT_T LCTL_T(KC_T)

// Right-hand home row mods
#define MT_N RCTL_T(KC_N)
#define MT_E RSFT_T(KC_E)
#define MT_I LALT_T(KC_I)
#define MT_O RGUI_T(KC_O)

#define MT_F11 GUI_T(KC_F11)
#define MT_F4 ALT_T(KC_F4)
#define MT_F5 SFT_T(KC_F5)
#define MT_F6 CTL_T(KC_F6)

#define CMD_GRV LCMD(KC_GRV)
#define BSP_WRD LCTL(KC_BSPC)

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_ALT OSM(MOD_LALT)

// clang-format off
#define ______BASE_THUMB_L______ TC_GUI, TC_SPC, TC_TAB
#define ______BASE_THUMB_R______ TC_ENT, KC_LSFT, TC_OPT

#define _________________COLEMAK_L1________________ KC_Q, KC_W, KC_F, KC_P, KC_B
#define _________________COLEMAK_L2________________ MT_A, MT_R, MT_S, MT_T, KC_G
#define _________________COLEMAK_L3________________ KC_Z, KC_X, KC_C, KC_D, KC_V

#define _________________COLEMAK_R1________________ KC_J, KC_L, KC_U, KC_Y, KC_QUOT
#define _________________COLEMAK_R2________________ KC_M, MT_N, MT_E, MT_I, MT_O
#define _________________COLEMAK_R3________________ KC_K, KC_H, KC_COMM, KC_DOT, KC_SLASH

#define _________________LOWER_L1__________________ KC_F12, KC_F7, KC_F8, KC_F9, XXXXXXX
#define _________________LOWER_L2__________________ MT_F11, MT_F4, MT_F5, MT_F6, KC_F13
#define _________________LOWER_L3__________________ KC_F10, KC_F1, KC_F2, KC_F3, XXXXXXX
#define _____LOWER_THUMB_L_____ _______, _______, _______

#define _________________LOWER_R1__________________ KC_PGUP, TD(NAV_BSPC), TD(NAV_UP),   TD(NAV_DEL),  XXXXXXX
#define _________________LOWER_R2__________________ KC_PGDN, TD(NAV_LEFT), TD(NAV_DOWN), TD(NAV_RGHT), XXXXXXX
#define _________________LOWER_R3__________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____LOWER_THUMB_R_____ _______, _______, _______

#define _________________RAISE_L1__________________ XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX
#define _________________RAISE_L2__________________ KC_ASTR, KC_4, KC_5, KC_6, KC_PLUS
#define _________________RAISE_L3__________________ KC_PIPE, KC_1, KC_2, KC_3, KC_DOT
#define _____RAISE_THUMB_L_____ XXXXXXX, KC_0, _______

#define _________________RAISE_R1__________________ XXXXXXX, KC_LBRC, KC_PIPE, KC_RBRC, KC_GRV
#define _________________RAISE_R2__________________ XXXXXXX, TD(MT_LPRN), TD(MT_EQL), TD(MT_RPRN), KC_RGUI
#define _________________RAISE_R3__________________ XXXXXXX, KC_LCBR, KC_TILD, KC_RCBR, KC_BSLS
#define _____RAISE_THUMB_R_____ _______, _______, _______

#define ________________ADJUST_L1__________________ RGB_MOD, RGB_IDL, KC_RGB_T, RGB_RMOD, XXXXXXX
#define ________________ADJUST_L2__________________ RGB_TOG, RGB_HUI, RGB_SAI,  RGB_VAI,  RGB_SPI
#define ________________ADJUST_L3__________________ RGBRST,  RGB_HUD, RGB_SAD,  RGB_VAD,  RGB_SPD

#define ________________ADJUST_R1__________________ XXXXXXX, KC_MPLY, KC_VOLU, KC_MUTE, QK_BOOT
#define ________________ADJUST_R2__________________ XXXXXXX, KC_MRWD, KC_VOLD, KC_MFFD, XXXXXXX
#define ________________ADJUST_R3__________________ XXXXXXX, DT_UP,   DT_DOWN, DT_PRNT, XXXXXXX

#define _________________MOUSE_L1__________________ _______, _______, _______, _______, _______
#define _________________MOUSE_L2__________________ OSM_GUI, OSM_ALT, OSM_SFT, OSM_CTL, _______
#define _________________MOUSE_L3__________________ _______, _______, _______, _______, _______
#define _____MOUSE_THUMB_L_____ XXXXXXX, XXXXXXX, XXXXXXX

#define _________________MOUSE_R1__________________ XXXXXXX, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX
#define _________________MOUSE_R2__________________ XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX
#define _________________MOUSE_R3__________________ XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, XXXXXXX
#define _____MOUSE_THUMB_R_____ KC_BTN1, KC_BTN2, XXXXXXX

#define ________________NUMBER_LEFT________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBER_RIGHT_______________ KC_6, KC_7, KC_8, KC_9, KC_0
#define ___________________BLANK___________________ _______, _______, _______, _______, _______

layer_state_t layer_state_set_keymap(layer_state_t state);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_change        : 1;
        bool     rgb_matrix_idle_anim    : 1;
        uint8_t  rgb_matrix_active_mode  : 4;
        uint8_t  rgb_matrix_idle_mode    : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed   : 8;
        uint16_t rgb_matrix_idle_timeout : 16;

    };
} userspace_config_t;
// clang-format on

extern userspace_config_t userspace_config;
