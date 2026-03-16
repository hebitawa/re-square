#include "lib_led.h"

#ifdef RGBLIGHT_LAYERS

const rgblight_segment_t PROGMEM rgb_layer_1st[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 170, 255, 100}  // BLUE
);
const rgblight_segment_t PROGMEM rgb_layer_2nd[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 0, 255, 100}    // RED
);
const rgblight_segment_t PROGMEM rgb_layer_3rd[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 85, 255, 100}   // GREEN
);
const rgblight_segment_t PROGMEM rgb_layer_4th[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 0, 0, 100}      // WHITE
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_1st,
    rgb_layer_2nd,
    rgb_layer_3rd,
    rgb_layer_4th
);

void led_post_init(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _1ST));
    rgblight_set_layer_state(1, layer_state_cmp(state, _2ND));
    rgblight_set_layer_state(2, layer_state_cmp(state, _3RD));
    rgblight_set_layer_state(3, layer_state_cmp(state, _4TH));
    return state;
}


/* -------- CPI表示点滅 -------- */

void led_blink_times(uint8_t times) {

    /* 現在のレイヤー状態保存 */
    bool l0 = rgblight_get_layer_state(0);
    bool l1 = rgblight_get_layer_state(1);
    bool l2 = rgblight_get_layer_state(2);
    bool l3 = rgblight_get_layer_state(3);

    /* レイヤー停止 */
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);
    rgblight_set_layer_state(3, false);

    for (uint8_t i = 0; i < times; i++) {

        rgblight_setrgb(255,255,255);
        wait_ms(250);

        rgblight_setrgb(0,0,0);
        wait_ms(250);
    }

    /* レイヤー復帰 */
    rgblight_set_layer_state(0, l0);
    rgblight_set_layer_state(1, l1);
    rgblight_set_layer_state(2, l2);
    rgblight_set_layer_state(3, l3);
}

#endif