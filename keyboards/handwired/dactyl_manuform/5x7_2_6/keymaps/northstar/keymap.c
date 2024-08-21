/* vim: noai:ts=4:sw=4:nowrap
*/
/*
Copyright 2012 Jun Wako <wakojun@gmail.com> Nikolai Grigoriev @ngrigoriev

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

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LOWER,
    _TYPING,
    _GAMING,
    _MAGIC,
    _CURSOR,
    _NUMPAD,
    _FN,
    _SYMBOL,
    _MOUSE,
    _SYS,
    _INTL
};

enum custom_keycodes {
  KVM_MAC_1 = SAFE_RANGE,
  KVM_LINUX_2,
  KVM_LINUX_3,
  KVM_LINUX_4,
};

// Some basic macros
#define TASK   LCTL(LSFT(KC_ESC))
#define TAB_R  LCTL(KC_TAB)
#define TAB_L  LCTL(LSFT(KC_TAB))
#define TAB_RO LCTL(LSFT(KC_T))

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_5x7_2_6(
        // Note: LALR_T on the right side, see https://precondition.github.io/home-row-mods about modifier handness
        KC_GRV,         KC_1,       KC_2,       KC_3,   KC_4,   KC_5,   MO(_MAGIC),                     KC_EQL,     KC_6,   KC_7,   KC_8,       KC_9,   KC_0,       KC_BSPC,
        KC_TAB,         KC_Q,       KC_W,       KC_E,   KC_R,   KC_T,   MO(_NUMPAD),                    KC_MINUS,   KC_Y,   KC_U,   KC_I,       KC_O,   KC_P,       KC_BSLS,
        KC_LCTL,        GUI_A,      ALT_S,      CTL_D,  SFT_F,  KC_G,   MO(_SYS),                       KC_DEL,     KC_H,   SFT_J,  CTL_K,      ALT_L,  GUI_SCLN,   KC_QUOT,
        OSM(MOD_LSFT),  KC_Z,       KC_X,       KC_C,   KC_V,   KC_B,                                               KC_N,   KC_M,   KC_COMM,    KC_DOT, KC_SLSH,    OSM(MOD_RSFT),
                                    KC_PGUP,    KC_PGDN,                                                                            KC_LBRC,    KC_RBRC,
                                                                KC_LCTL, LT(_FN, KC_ESC),               KC_SPC, KC_ENTER,
                                                                        KC_UP,      KC_DOWN,    KC_LEFT,    KC_RIGHT,
                                                                        KC_LCMD,    KC_LALT,    KC_RCTL,    KC_RALT
    ),

    [_FN] = LAYOUT_5x7_2_6(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      MO(_MAGIC),             _______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
        _______,    _______,    _______,    KC_UP,      _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    KC_F12,
        _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,    KC_INT1,                _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    _______,
                                KC_MPRV,    KC_MNXT,                                                                                        _______,    _______,
                                                                    _______,    _______,                KC_DEL, _______,
                                                                            _______,    _______,    _______, _______,
                                                                            _______,    _______,    _______, _______
    ),

    [_NUMPAD] = LAYOUT_5x7_2_6(
        _______,    _______,    _______,    _______,    _______,    _______,    MO(_MAGIC),             _______,    _______,    KC_NUM,     _______,    KC_PMNS,    KC_PPLS,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    KC_P7,      KC_P8,      KC_P9,      _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    KC_P4,      KC_P5,      KC_P6,      KC_PAST,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    KC_P1,      KC_P2,      KC_P3,      KC_PSLS,    _______,
                                _______,    _______,                                                                                        KC_P0,      KC_PDOT,
                                                                    _______,    _______,                _______,    KC_PENT,
                                                                            _______,    _______,    _______,    _______,
                                                                            _______,    _______,    _______,    _______
    ),

    [_MAGIC] = LAYOUT_5x7_2_6(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                CG_SWAP,    _______,    _______,    _______,    _______,    _______,    QK_REBOOT,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                CG_NORM,    _______,    _______,    _______,    _______,    _______,    QK_BOOTLOADER,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    _______,
                                _______,    _______,                                                                                        _______,    _______,
                                                                    _______,    _______,                _______,    _______,
                                                                            _______,    _______,    _______,    _______,
                                                                            _______,    _______,    _______,    _______
    ),
    [_SYS] = LAYOUT_5x7_2_6(
        _______,    _______,    _______,    _______,    _______,    _______,    MO(_MAGIC),             CG_SWAP,    _______,    _______,    _______,    _______,    _______,    KVM_MAC_1,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    KVM_LINUX_2,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                CG_NORM,    _______,    _______,    _______,    _______,    _______,    KVM_LINUX_3,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    KVM_LINUX_4,
                                _______,    _______,                                                                                        _______,    _______,
                                                                    _______,    _______,                _______,    _______,
                                                                            _______,    _______,    _______,    _______,
                                                                            _______,    _______,    KC_SCRL,    _______
    )
};



bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    // option 1
    if (IS_RETRO(keycode))
        return true;
    return false;
}
