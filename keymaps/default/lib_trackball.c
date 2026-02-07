#include QMK_KEYBOARD_H
#include "lib_trackball.h"

#define SCROLL_DIVISOR_H 100.0
#define SCROLL_DIVISOR_V 100.0

bool set_scrolling = false;
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

void trackball_post_init(void) {
#ifdef POINTING_DEVICE_COMBINED
    pointing_device_set_cpi_on_side(false, PMW33XX_CPI);
    pointing_device_set_cpi_on_side(true, PMW33XX_CPI * 2);
#endif
}

#ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    if (set_scrolling) {
        scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

        right_report.h = (int8_t)scroll_accumulated_h;
        right_report.v = -(int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        right_report.x = 0;
        right_report.y = 0;
    } else {
        scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        left_report.h = (int8_t)scroll_accumulated_h;
        left_report.v = -(int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    }

    left_report.x = 0;
    left_report.y = 0;
    
    return pointing_device_combine_reports(left_report, right_report);
}
#endif