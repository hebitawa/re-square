/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "print.h"
#include "library/lib_trackball.h"
#include "library/lib_led.h"

#define ____    KC_TRNS
#define XXXX    KC_NO

enum custom_keycodes {
    CPI_NEXT = SAFE_RANGE,
    TB_PRECISION,
    TB_SCROLL,
    /*TB_SWAP,*/
    TB_DUAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS,
		KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		KC_UP,     XXXX,   KC_LALT, LT(3, KC_SPC),  MO(3),    KC_LEFT, KC_DOWN, KC_RGHT, LT(2, JP_MHEN),
		XXXX,     MO(3),    LT(1, JP_HENK),   KC_ENT,  KC_RGHT, KC_UP,   KC_LEFT, KC_RGUI, KC_DOWN
	),
	[1] = LAYOUT(
		KC_7, KC_8, KC_9, KC_F7, KC_F8, KC_F9, KC_F7, KC_F8, KC_F9, KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6, KC_F4, KC_F5, KC_F6, KC_F4, KC_F5, KC_F6, KC_4, KC_5, KC_6,
		KC_1, KC_2, KC_3, KC_F1, KC_F2, KC_F3, KC_F1, KC_F2, KC_F3, KC_1, KC_2, KC_3,
		KC_0, KC_F10, KC_DOT, ____, KC_F11, ____, ____, ____, KC_F12,
		KC_F10, KC_F11, KC_F12, ____, ____, KC_0, ____, KC_DOT, ____
	),
	[2] = LAYOUT(
		____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____
	),
	[3] = LAYOUT(
		____, CPI_NEXT, TB_SCROLL, TB_DUAL, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, TB_PRECISION, ____, ____, MS_BTN1, MS_BTN2, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____,
		____, ____, ____, ____, ____, ____, ____, ____, ____
	)
};


void keyboard_post_init_user(void) {
    trackball_post_init();
    led_post_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case CPI_NEXT:
            if (record->event.pressed) {
                trackball_cycle_cpi();
            }
            return false;

        case TB_PRECISION:
            trackball_precision_mode(record->event.pressed);
            return false;

        case TB_SCROLL:
            if (record->event.pressed) {
                trackball_scroll_toggle();
            }
            return false;

		case TB_DUAL:
            if (record->event.pressed) {
                trackball_dual_cursor_toggle();
            }
            return false;

/*		case TB_SWAP:
            if (record->event.pressed) {
                trackball_swap_toggle();
            }
            return false; */
    }
    return true;

}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN) },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN) },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN) },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN) },
};
#endif