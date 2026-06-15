BOOTMAGIC_ENABLE = yes  # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
WPM_ENABLE = yes

INTROSPECTION_KEYMAP_C = mforman.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled/oled.c
endif

VPATH += keyboards/gboards/
COMBO_ENABLE = yes
