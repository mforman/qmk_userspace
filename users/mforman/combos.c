// QWERTY
const uint16_t PROGMEM weEsc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM sdBspc[] = {MT_S_Q, MT_D, COMBO_END};
const uint16_t PROGMEM asdBspc[] = {MT_A, MT_S_Q, MT_D, COMBO_END};
const uint16_t PROGMEM dfTab[] = {MT_D, MT_F, COMBO_END};
const uint16_t PROGMEM sdfAltTab[] = {MT_S_Q, MT_D, MT_F, COMBO_END};
const uint16_t PROGMEM uiBckSlsh[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM jkDash[] = {MT_J, MT_K, COMBO_END};
const uint16_t PROGMEM klColon[] = {MT_K, MT_L, COMBO_END};
const uint16_t PROGMEM mCommUnd[] = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM commDotScl[] = {KC_COMMA, KC_DOT, COMBO_END};

// COLEMAK
const uint16_t PROGMEM wfEsc[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM rsBspc[] = {MT_R, MT_S, COMBO_END};
const uint16_t PROGMEM arsBspc[] = {MT_A, MT_R, MT_S, COMBO_END};
const uint16_t PROGMEM stTab[] = {MT_S, MT_T, COMBO_END};
const uint16_t PROGMEM rstAltTab[] = {MT_R, MT_S, MT_T, COMBO_END};
const uint16_t PROGMEM luBckSlsh[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM neDash[] = {MT_N, MT_E, COMBO_END};
const uint16_t PROGMEM eiColon[] = {MT_E, MT_I, COMBO_END};
const uint16_t PROGMEM hCommUnd[] = {KC_H, KC_COMMA, COMBO_END};

// Others
const uint16_t PROGMEM volDwnUp[] = {KC_VOLD, KC_VOLU, COMBO_END};
const uint16_t PROGMEM spcTabCmdCt[] = {TC_SPC, TC_TAB, COMBO_END};
const uint16_t PROGMEM entBspc[] = {TC_BSP, TC_ENT, COMBO_END};
const uint16_t PROGMEM grvSft[] = {KC_GRV, KC_RCTL, COMBO_END};

combo_t key_combos[] = {
    COMBO(weEsc, KC_ESC),
    COMBO(sdBspc, KC_BSPC),
    COMBO(asdBspc, BSP_WRD),
    COMBO(dfTab, KC_TAB),
    COMBO(sdfAltTab, ALT_TAB),
    COMBO(uiBckSlsh, KC_BSLS),
    COMBO(jkDash, KC_MINS),
    COMBO(klColon, KC_COLN),
    COMBO(mCommUnd, KC_UNDS),
    COMBO(commDotScl, KC_SCLN),

    COMBO(wfEsc, KC_ESC),
    COMBO(rsBspc, KC_BSPC),
    COMBO(arsBspc, BSP_WRD),
    COMBO(stTab, KC_TAB),
    COMBO(rstAltTab, ALT_TAB),
    COMBO(luBckSlsh, KC_BSLS),
    COMBO(neDash, KC_MINS),
    COMBO(eiColon, KC_COLN),
    COMBO(hCommUnd, KC_UNDS),

    COMBO(volDwnUp, KC_MUTE),
    COMBO(spcTabCmdCt, LCTL(KC_LGUI)),
    COMBO(entBspc, KC_DEL),
    COMBO(grvSft, CMD_GRV)
};
