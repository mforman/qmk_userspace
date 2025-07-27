/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// #define USE_MATRIX_I2C

/* Select hand configuration */
#define EE_HANDS

#define SSD1306OLED
#undef USE_I2C
// #undef SSD1306OLED

#define USE_SERIAL_PD2

#define LAYER_STATE_8BIT

#define OLED_FONT_H "users/mforman/oled/glcdfont.c"

#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES

#ifdef RGB_MATRIX_ENABLE
#  define RGB_MATRIX_KEYREACTIVE_ENABLED

// Since we have PaletteFx, disable most built-in RGB Matrix effects.
#  undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#  undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#  undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#  undef ENABLE_RGB_MATRIX_BREATHING
#  undef ENABLE_RGB_MATRIX_BAND_SAT
#  undef ENABLE_RGB_MATRIX_BAND_VAL
#  undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#  undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#  undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#  undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#  undef ENABLE_RGB_MATRIX_CYCLE_ALL
#  undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#  undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#  undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#  undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#  undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#  undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#  undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#  undef ENABLE_RGB_MATRIX_DUAL_BEACON
#  undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#  undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#  undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#  undef ENABLE_RGB_MATRIX_RAINDROPS
#  undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#  undef ENABLE_RGB_MATRIX_HUE_BREATHING
#  undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#  undef ENABLE_RGB_MATRIX_HUE_WAVE
#  undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#  undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#  undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#  undef ENABLE_RGB_MATRIX_STARLIGHT
#  undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#  undef ENABLE_RGB_MATRIX_RIVERFLOW

#  undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#  undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#  undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#  undef ENABLE_RGB_MATRIX_SPLASH
#  undef ENABLE_RGB_MATRIX_MULTISPLASH
#  undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#  undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif  // RGB_MATRIX_ENABLE
