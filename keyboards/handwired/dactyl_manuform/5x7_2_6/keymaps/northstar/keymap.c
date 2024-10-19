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
    _EMAIL, // AKA Emoji
    _NUMBER, // AKA Numpad
    _FN,    // AKA Function
    _SYMBOL,
    _MOUSE,
    _SYS,
    _WORLD
};

enum custom_keycodes {
    KVM_MAC_1 = SAFE_RANGE,
    KVM_LINUX_2,
    KVM_LINUX_3,
    KVM_LINUX_4,
    KCC_URL,
    KCC_FREP,
    KCC_ALT_TAB,
    KCC_GUI_TAB,
    KCC_CTL_TAB,
    KCC_SEL_ALL,
    KCC_SEL_NONE,
    KCC_SEL_WRD,
    KCC_SEL_LIN,
    KCC_LOCK
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

#define LY_LOWER MO(_LOWER)
#define LY_MAGIC MO(_MAGIC)
#define STICKY_LSFT OSM(MOD_LSFT)
#define STICKY_RSFT OSM(MOD_RSFT)

#define ESC_LT_FN LT(_FN, KC_ESC)
#define ENTER_LT_SYS LT(_SYS, KC_ENTER)
#define SPC_LT_SYMBOL LT(_SYMBOL, KC_SPC)
#define TAB_LT_MOUSE LT(_MOUSE, KC_TAB)
#define LBRC_LT_WORLD LT(_WORLD, KC_LBRC)
#define BSPC_LT_CURSOR LT(_CURSOR, KC_BSPC)
#define PGDN_LT_EMAIL LT(_EMAIL, KC_PGDN)
#define DEL_LT_NUMBER LT(_NUMBER, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_5x7_2_6(
        // Note: LALR_T on the right side, see https://precondition.github.io/home-row-mods about modifier handness
        KC_GRV,         KC_1,       KC_2,       KC_3,   KC_4,   KC_5,   KC_MINUS,                       KC_EQL,     KC_6,   KC_7,   KC_8,           KC_9,       KC_0,       KC_BSPC,
        KC_TAB,         KC_Q,       KC_W,       KC_E,   KC_R,   KC_T,   KC_QUOT,                        KC_BSLS,    KC_Y,   KC_U,   KC_I,           KC_O,       KC_P,       _______,
        STICKY_LSFT,    GUI_A,      ALT_S,      CTL_D,  SFT_F,  KC_G,   KC_HOME,                        KC_END,     KC_H,   SFT_J,  CTL_K,          ALT_L,      GUI_SCLN,   STICKY_RSFT,
        LY_MAGIC,       KC_Z,       KC_X,       KC_C,   KC_V,   KC_B,                                               KC_N,   KC_M,   KC_COMM,        KC_DOT,     KC_SLSH,    LY_MAGIC,
                                    KC_PGUP,    PGDN_LT_EMAIL,                                                                      LBRC_LT_WORLD,  KC_RBRC,
                                                                BSPC_LT_CURSOR, ESC_LT_FN,            SPC_LT_SYMBOL, ENTER_LT_SYS,
                                                                        KC_UP,          KC_DOWN,    KC_LEFT,    KC_RIGHT,
                                                                        DEL_LT_NUMBER,  LY_LOWER,   LY_LOWER,   TAB_LT_MOUSE
    ),

    [_LOWER] = LAYOUT_5x7_2_6(
        KC_GRV,         KC_BRIU,    KC_BRID,    KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_MINUS,               KC_EQL,     KC_LPRN,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_KP_ASTERISK, KC_PAUS,
        KC_TAB,         _______,    _______,    _______,    KC_UP,      _______,    KC_SCRL,                KC_NUM,     KC_RPRN,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_MINUS,    _______,
        KC_ESC,         KC_APP,     _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_HOME,                KC_END,     KC_PERC,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_PLUS,     KC_KP_ENTER,
        LY_MAGIC,       KC_CAPS,    KC_INS,     _______,    KC_F11,     KC_F12,                                         KC_COMM,    KC_KP_1,    KC_KP_2,    KC_KP_3,    _______,        LY_MAGIC,
                                    KC_PGUP,    TO(_EMAIL),                                                                                     KC_KP_0,    KC_KP_DOT,
                                                                        TO(_CURSOR),   TO(_FN),                TO(_SYMBOL),    TO(_SYS),
                                                                                TO(_TYPING),TO(_GAMING),TO(_GAMING),TO(_TYPING),
                                                                                TO(_NUMBER),TO(_BASE),    TO(_BASE),TO(_MOUSE)
    ),

    [_FN] = LAYOUT_5x7_2_6(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      MO(_MAGIC),             _______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
        _______,    _______,    _______,    KC_UP,      _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    KC_F12,
        _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,    KC_INT1,                _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    _______,
                                KC_MPRV,    KC_MNXT,                                                                                        _______,    _______,
                                                                    _______,    _______,                KC_DEL, _______,
                                                                            _______,    _______,    _______, _______,
                                                                            _______,    TO(_BASE),  TO(_BASE), _______
    ),

    [_NUMBER] = LAYOUT_5x7_2_6(
        _______,    _______,    _______,    _______,    _______,    _______,    MO(_MAGIC),             _______,    _______,    KC_NUM,     _______,    KC_PMNS,    KC_PPLS,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    KC_P7,      KC_P8,      KC_P9,      _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    KC_P4,      KC_P5,      KC_P6,      KC_PAST,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    KC_P1,      KC_P2,      KC_P3,      KC_PSLS,    _______,
                                _______,    _______,                                                                                        KC_P0,      KC_PDOT,
                                                                    _______,    _______,                _______,    KC_PENT,
                                                                            _______,    _______,    _______,    _______,
                                                                            _______,    TO(_BASE),  TO(_BASE),  _______
    ),

    [_MAGIC] = LAYOUT_5x7_2_6(
        QK_REBOOT,      TO(1),      TO(1),      TO(3),      TO(4),      TO(5),      _______,                CG_SWAP,    TO(6),      TO(7),      TO(8),      TO(9),      TO(0),      QK_REBOOT,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        QK_BOOTLOADER,  _______,    _______,    _______,    _______,    _______,    _______,                CG_NORM,    _______,    _______,    _______,    _______,    _______,    QK_BOOTLOADER,
        _______,        _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    _______,
                                    _______,    _______,                                                                                        _______,    _______,
                                                                        _______,    _______,                _______,    _______,
                                                                                _______,    _______,    _______,    _______,
                                                                                _______,    TO(_BASE),  TO(_BASE),  _______
    ),
    // TBC
    [_CURSOR] = LAYOUT_5x7_2_6(
        KC_ESC,         _______,    _______,    _______,    _______,    _______,    _______,                        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        KCC_URL,        _______,    _______,    _______,    _______,    _______,    _______,                        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        KCC_FREP,       _______,    _______,    _______,    _______,    _______,    _______,                        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        LY_MAGIC,       _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    LY_MAGIC,
                                    _______,    _______,                                                                                        _______,    _______,
                                                                        KC_TAB,    _______,                         KCC_SEL_NONE,KCC_SEL_ALL,
                                                                                KCC_ALT_TAB,KCC_GUI_TAB,    KCC_SEL_LIN,KCC_SEL_WRD,
                                                                                KCC_CTL_TAB,TO(_BASE),      TO(_BASE),  _______
    ),

    [_SYS] = LAYOUT_5x7_2_6(
        _______,    _______,    _______,    _______,    _______,    _______,    MO(_MAGIC),             CG_SWAP,    KC_RSFT,    KC_RCTL,    KC_RALT,    KC_RGUI,    _______,    KVM_MAC_1,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    KC_APP,     KCC_LOCK,   KC_SLEP,    KC_PWR,     _______,    KVM_LINUX_2,
        _______,    _______,    _______,    _______,    _______,    _______,    KC_APP,                 CG_NORM,    _______,    KC_PSCR,    KC_SCRL,    KC_BRK,     _______,    KVM_LINUX_3,
        _______,    _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    KVM_LINUX_4,
                                _______,    _______,                                                                                        _______,    _______,
                                                                    KC_SLEP,    KC_PWR,                _______,    _______,
                                                                            KC_SCRL,    _______,    _______,    KC_SCRL,
                                                                            KC_PSCR,    TO(_BASE),  TO(_BASE),  KC_SYRQ
    ),
    // TODO
    [_TYPING] = LAYOUT_5x7_2_6(
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        LY_MAGIC,       _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    LY_MAGIC,
                                    _______,    _______,                                                                                        _______,    _______,
                                                                        _______,    _______,                _______,    _______,
                                                                                _______,    _______,    _______,    _______,
                                                                                _______,    TO(_BASE),  TO(_BASE),  _______
    ),
    [_GAMING] = LAYOUT_5x7_2_6(
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        LY_MAGIC,       _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    LY_MAGIC,
                                    _______,    _______,                                                                                        _______,    _______,
                                                                        _______,    _______,                _______,    _______,
                                                                                _______,    _______,    _______,    _______,
                                                                                _______,    TO(_BASE),  TO(_BASE),    _______
    ),
//    [_NONE] = LAYOUT_5x7_2_6(
//        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
//        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
//        _______,        _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,
//        LY_MAGIC,       _______,    _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    LY_MAGIC,
//                                    _______,    _______,                                                                                        _______,    _______,
//                                                                        _______,    _______,                _______,    _______,
//                                                                                _______,    _______,    _______,    _______,
//                                                                                _______,    _______,    _______,    _______
};



// not using this now since auto-shift is off
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    // option 1
//    if (IS_RETRO(keycode))
//        return true;
    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int kvm_port_keys[] = {KC_1, KC_2, KC_3, KC_4};
    switch (keycode) {
    case KVM_MAC_1:
    case KVM_LINUX_2:
    case KVM_LINUX_3:
    case KVM_LINUX_4:
        tap_code(KC_SCRL);
        tap_code(KC_SCRL);
        tap_code(kvm_port_keys[keycode - KVM_MAC_1]);
        // for Mac we swap the control and command keys
        // This code is copied from process_magic.c, there is no way to send CG_NORM|
        // SWAP magic key codes using tap_code
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = keycode == KVM_MAC_1;
        break;
    }
    return true;
};
