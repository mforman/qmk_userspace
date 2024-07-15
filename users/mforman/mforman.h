#pragma once

#include QMK_KEYBOARD_H

#include "eeprom.h"
#include "switcher/switcher.h"
#include "version.h"
#ifdef OLED_DRIVER_ENABLE
#    include "oled/oled.h"
#endif

// clang-format off
enum keyboard_layers {
    _COLEMAK = 0,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST };

enum mforman_keycodes {
    ALT_TAB = SAFE_RANGE,
    BSP_WRD,
    RGB_IDL,
    KC_RGB_T,
    RGBRST,
    COLEMAK,
    QWERTY,
    TG_WIN };
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

// Colemak
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

// QWERTY
// Left-hand home row mods
// #define MT_A LCTL_T(KC_A)
#define MT_S_Q LALT_T(KC_S)
#define MT_D LSFT_T(KC_D)
#define MT_F LCTL_T(KC_F)

// Right-hand home row mods
#define MT_J RCTL_T(KC_J)
#define MT_K RSFT_T(KC_K)
#define MT_L LALT_T(KC_L)
#define MT_QUOT RGUI_T(KC_QUOT)

#define MT_F11 GUI_T(KC_F11)
#define MT_F4 ALT_T(KC_F4)
#define MT_F5 SFT_T(KC_F5)
#define MT_F6 CTL_T(KC_F6)

#define MT_LBRC RCTL_T(KC_LBRC)
#define MT_EQL RSFT_T(KC_EQL)
#define MT_RBRC LALT_T(KC_RBRC)

#define CMD_GRV LCMD(KC_GRV)

#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_ALT OSM(MOD_LALT)

// clang-format off
#define ______BASE_THUMB_L______ TC_GUI, TC_SPC, TC_TAB
#define ______BASE_THUMB_R______ TC_ENT, TC_BSP, TC_OPT

#define _________________QWERTY_L1_________________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define _________________QWERTY_L2_________________ MT_A, MT_S_Q, MT_D, MT_F, KC_G
#define _________________QWERTY_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_B

#define _________________QWERTY_R1_________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define _________________QWERTY_R2_________________ KC_H, MT_J, MT_K, MT_L, MT_QUOT
#define _________________QWERTY_R3_________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH

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

#define _________________LOWER_R1__________________ KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  XXXXXXX
#define _________________LOWER_R2__________________ KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX
#define _________________LOWER_R3__________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____LOWER_THUMB_R_____ _______, _______, _______

#define _________________RAISE_L1__________________ XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX
#define _________________RAISE_L2__________________ KC_ASTR, KC_4, KC_5, KC_6, KC_PLUS
#define _________________RAISE_L3__________________ KC_PIPE, KC_1, KC_2, KC_3, KC_DOT
#define _____RAISE_THUMB_L_____ XXXXXXX, KC_0, _______

#define _________________RAISE_R1__________________ XXXXXXX, KC_LPRN, KC_PIPE, KC_RPRN, KC_GRV
#define _________________RAISE_R2__________________ XXXXXXX, MT_LBRC, MT_EQL,  MT_RBRC, KC_RGUI
#define _________________RAISE_R3__________________ XXXXXXX, KC_LCBR, KC_TILD, KC_RCBR, KC_BSLS
#define _____RAISE_THUMB_R_____ _______, _______, _______

#define ________________ADJUST_L1__________________ RGB_MOD, RGB_IDL, KC_RGB_T, RGB_RMOD, XXXXXXX
#define ________________ADJUST_L2__________________ RGB_TOG, RGB_HUI, RGB_SAI,  RGB_VAI,  RGB_SPI
#define ________________ADJUST_L3__________________ RGBRST,  RGB_HUD, RGB_SAD,  RGB_VAD,  RGB_SPD

#define ________________ADJUST_R1__________________ XXXXXXX, CG_TOGG, QWERTY,  COLEMAK, QK_BOOT
#define ________________ADJUST_R2__________________ KC_MPLY, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD
#define ________________ADJUST_R3__________________ XXXXXXX, DT_UP,   DT_DOWN, DT_PRNT, XXXXXXX

#define ________________NUMBER_LEFT________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBER_RIGHT_______________ KC_6, KC_7, KC_8, KC_9, KC_0
#define ___________________BLANK___________________ _______, _______, _______, _______, _______

layer_state_t layer_state_set_keymap(layer_state_t state);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);

typedef union {
    uint32_t raw;
    struct {
        bool     is_mac_os               : 1;
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
