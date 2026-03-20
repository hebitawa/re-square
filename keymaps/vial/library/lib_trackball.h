#pragma once
#include "quantum.h"

extern bool set_scrolling;

void trackball_post_init(void);
void trackball_cycle_cpi(void);
void trackball_precision_mode(bool enable);
void trackball_scroll_toggle(void);
void trackball_dual_cursor_toggle(void);