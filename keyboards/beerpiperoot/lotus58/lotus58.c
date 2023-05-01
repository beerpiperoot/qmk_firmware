// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
char host_led_state_str[26];

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
	// Rotate OLED to fit
    if (is_keyboard_left()) {
        return OLED_ROTATION_90;
	}
    return OLED_ROTATION_270;
}

const char *read_host_led_state(void)
{
  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s\nCL:%s\nSL:%s",
           (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) ? "on" : "- ",
           (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) ? "on" : "- ",
           (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) ? "on" : "- ");

  return host_led_state_str;
}

static void print_status_narrow(void) {
    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base\n"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Num\n"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Func\n"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Sys \n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n"), false);
    oled_write(read_host_led_state(), false);
}

bool oled_task_kb(void) {
    // render_logo();
	print_status_narrow();
	return false;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
	// Allow switching to the 'hidden' layer
   return update_tri_layer_state(state, 1, 2, 3);
}
