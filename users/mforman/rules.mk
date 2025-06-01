BOOTMAGIC_ENABLE = yes  # Enable Bootmagic Lite
COMBO_ENABLE	 = yes
MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
SWITCHER_ENABLE  = no
DYNAMIC_TAPPING_TERM_ENABLE = yes
WPM_ENABLE = no

INTROSPECTION_KEYMAP_C = mforman.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled/oled.c
endif

ifeq ($(strip $(SWITCHER_ENABLE)), yes)
	SRC += $(USER_PATH)/switcher/switcher.c
endif
