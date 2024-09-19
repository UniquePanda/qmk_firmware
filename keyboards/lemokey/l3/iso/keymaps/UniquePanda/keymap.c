/* Copyright 2023 @ Lemokey (https://www.lemokey.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "lemokey_common.h"


enum layer_names {
    BASE = 0,
    FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_iso_tkl(
                  KC_MPLY,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   MC_0,     KC_LOCK,  RGB_TOG,
                  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        MC_1,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_ENT,   KC_DEL,   KC_END,   KC_PGDN,
        MC_2,     KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,
        KC_NO,    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_NO,    KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MC_30,      KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),
    [FN] = LAYOUT_iso_tkl(
                  _______,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  BAT_LVL,
                  _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,  _______,                                _______,                                _______,  _______,  MC_31,      _______,  _______,  _______,  _______),
};
// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]   = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_lemokey_common(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case MC_0:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_PEQL) SS_UP(X_LCTL));
            return false;
        case MC_1:
            SEND_STRING("10k");
            return false;
        case MC_2:
            SEND_STRING("10j");
            return false;
        case MC_30:
            layer_move(FN);
            #ifdef LED_CAPS_LOCK_PIN
                //setPinOutput(LED_CAPS_LOCK_PIN);
                writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
            #endif
            return false;
        case MC_31:
            layer_move(BASE);
            #ifdef LED_CAPS_LOCK_PIN
                //setPinOutput(LED_CAPS_LOCK_PIN);
                writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
            #endif
            return false;
    }

    return true;
}

