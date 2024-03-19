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
