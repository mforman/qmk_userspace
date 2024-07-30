#ifdef COMBO_ENABLE
#    define COMBO_ALLOW_ACTION_KEYS
#    define COMBO_VARIABLE_LEN

#    ifdef COMBO_TERM
#        undef COMBO_TERM
#    endif
#    define COMBO_TERM 30
#endif

#define ONESHOT_TIMEOUT 1000 /* Time (in ms) before the one shot key is released */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
