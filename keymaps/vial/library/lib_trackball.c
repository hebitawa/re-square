#include QMK_KEYBOARD_H
#include "lib_trackball.h"
#include "lib_led.h"

#define SCROLL_DIVISOR_H 70.0
#define SCROLL_DIVISOR_V 70.0

#define PRECISION_CPI 800

bool set_scrolling = false;

/* 左右役割反転フラグ */
bool swap_trackball = false;

float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;


/* ---------- CPI設定 ---------- */

static const uint16_t cursor_cpi_list[] = {
    800,
    1200,
    1600,
    2400,
    3200
};

static uint8_t cursor_cpi_index = 2;


/* ---------- 初期化 ---------- */

void trackball_post_init(void) {

#ifdef POINTING_DEVICE_COMBINED

    pointing_device_set_cpi_on_side(true,  cursor_cpi_list[cursor_cpi_index]);
    pointing_device_set_cpi_on_side(false, cursor_cpi_list[cursor_cpi_index]);

#else

    pointing_device_set_cpi(cursor_cpi_list[cursor_cpi_index]);

#endif
}


/* ---------- CPI切替 ---------- */

void trackball_cycle_cpi(void) {

    cursor_cpi_index = (cursor_cpi_index + 1) % 5;

#ifdef POINTING_DEVICE_COMBINED

    pointing_device_set_cpi_on_side(true,  cursor_cpi_list[cursor_cpi_index]);
    pointing_device_set_cpi_on_side(false, cursor_cpi_list[cursor_cpi_index]);

#else

    pointing_device_set_cpi(cursor_cpi_list[cursor_cpi_index]);

#endif

    led_blink_times(cursor_cpi_index + 1);
}


/* ---------- 精密モード ---------- */

void trackball_precision_mode(bool enable) {

#ifdef POINTING_DEVICE_COMBINED

    if (enable) {

        pointing_device_set_cpi_on_side(true,  PRECISION_CPI);
        pointing_device_set_cpi_on_side(false, PRECISION_CPI);

    } else {

        pointing_device_set_cpi_on_side(true,  cursor_cpi_list[cursor_cpi_index]);
        pointing_device_set_cpi_on_side(false, cursor_cpi_list[cursor_cpi_index]);

    }

#else

    if (enable) {
        pointing_device_set_cpi(PRECISION_CPI);
    } else {
        pointing_device_set_cpi(cursor_cpi_list[cursor_cpi_index]);
    }

#endif
}


/* ---------- スクロール切替 ---------- */

void trackball_scroll_toggle(void) {

    set_scrolling = !set_scrolling;
}


/* 左右役割反転(実装中) */

void trackball_swap_toggle(void) {

    swap_trackball = !swap_trackball;

}


/* ---------- メイン処理 ---------- */

#ifdef POINTING_DEVICE_COMBINED

report_mouse_t pointing_device_task_combined_user(
    report_mouse_t left_report,
    report_mouse_t right_report
) {

    /* ---------- 通常配置 ---------- */
    if (!swap_trackball) {

        /* 左 → スクロール */

        scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        left_report.h = (int8_t)scroll_accumulated_h;
        left_report.v = -(int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        left_report.x = 0;
        left_report.y = 0;

        /* 右 → カーソル or スクロール */

        if (set_scrolling) {

            scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
            scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

            right_report.h = (int8_t)scroll_accumulated_h;
            right_report.v = -(int8_t)scroll_accumulated_v;

            scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
            scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

            right_report.x = 0;
            right_report.y = 0;
        }

    }

    /* ---------- 反転配置 ---------- */
    else {

        /* 右 → スクロール */

        scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

        right_report.h = (int8_t)scroll_accumulated_h;
        right_report.v = -(int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        right_report.x = 0;
        right_report.y = 0;

        /* 左 → カーソル or スクロール */

        if (set_scrolling) {

            scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
            scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

            left_report.h = (int8_t)scroll_accumulated_h;
            left_report.v = -(int8_t)scroll_accumulated_v;

            scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
            scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

            left_report.x = 0;
            left_report.y = 0;
        }

    }

    return pointing_device_combine_reports(left_report, right_report);
}

#endif