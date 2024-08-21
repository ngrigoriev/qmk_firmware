/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#undef PRODUCT
#define PRODUCT "Dactyl Manuform 5x7_2_6 Northstar layout"

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// because the right half needs its own one - rightmost top key on the right half (labeled KC_BSPC)
#define BOOTMAGIC_ROW_RIGHT 6
#define BOOTMAGIC_COLUMN_RIGHT 6

#define TAPPING_TERM 200
// this allows quick consecutive taps of home mod key followed by the same key used as modifier
#define QUICK_TAP_TERM 0
// this allows not to wait for the end of TAPPING_TERM before the key works as a modifier IF another
// key is pressed quickly. Not recommended unless TAPPING_TERM is high.
#undef PERMISSIVE_HOLD

// not to use with home row mods
#undef HOLD_ON_OTHER_KEYPRESS

// retro tap control
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_LEFT_GUI), MOD_BIT(KC_RIGHT_GUI), MOD_BIT(KC_LEFT_CTRL)|MOD_BIT(KC_LEFT_SHIFT) }

#define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT 200
#define AUTO_SHIFT_NO_AUTO_REPEAT

#define RETRO_SHIFT 1000
