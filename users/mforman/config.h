#ifdef COMBO_ENABLE
#    define COMBO_ALLOW_ACTION_KEYS
#    define COMBO_VARIABLE_LEN

#    ifdef COMBO_TERM
#        undef COMBO_TERM
#    endif
#    define COMBO_TERM 30
#endif

#define LAYER_COLEMAK 0
#define LAYER_LOWER   1
#define LAYER_RAISE   2
#define LAYER_ADJUST  3

#define TRI_LAYER_LOWER_LAYER  LAYER_LOWER
#define TRI_LAYER_UPPER_LAYER  LAYER_RAISE
#define TRI_LAYER_ADJUST_LAYER LAYER_ADJUST

#define ONESHOT_TIMEOUT 1000 /* Time (in ms) before the one shot key is released */
#define TAPPING_TERM 250
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
