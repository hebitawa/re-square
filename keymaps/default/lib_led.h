#pragma once
#include QMK_KEYBOARD_H

enum layer_number {
  _1ST = 0,
  _2ND,
  _3RD,
  _4TH
};

void led_post_init(void);