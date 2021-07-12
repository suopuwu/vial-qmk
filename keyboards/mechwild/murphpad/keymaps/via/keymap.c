/* Copyright 2021 Kyle McCreery
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
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE,
  _FN1
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                  KC_MPLY,   KC_MPRV,   KC_MNXT,   TG(_FN1),
				          KC_COMM, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_COMM,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_DEL, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_BSPC,  KC_P0,   KC_P0,   KC_PDOT, KC_PENT,
		
				          KC_F5,   KC_F6,   KC_F7

    ),
	
    [_FN1] = LAYOUT(
                 KC_MPLY,   KC_MPRV,   KC_MNXT,   KC_TRNS,
                 KC_1,     KC_2,    KC_3,    KC_4,
                 KC_Q,     KC_W,    KC_E,    KC_R,
        KC_TAB,  KC_A,     KC_S,    KC_D,    KC_F,
        KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,
        KC_LCTL, KC_LGUI,  KC_LALT, KC_SPC, KC_SPC,
		
                 _______,  _______, _______

    )
};



#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    return true;
}
#endif

#ifdef OLED_DRIVER_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;       // flips the display 270 degrees
	}
	static void render_image(void) {
    static const char PROGMEM qmk_logo[] = {
			// 'idso1kjm4im51', 32x128px
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x0f, 
			0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0xff, 0xff, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0xc1, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0xc0, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe0, 
			0xf3, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x78, 
			0x7c, 0x7c, 0xfe, 0xff, 0xff, 0xff, 0xe0, 0xc0, 0x00, 0x00, 0x0c, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 
			0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x3c, 0x18, 0x98, 0x98, 
			0x18, 0x00, 0x00, 0x01, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xfc, 0xe4, 0xe0, 0x80, 0x80, 
			0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 
			0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
			0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 
			0xff, 0xff, 0xfb, 0xf3, 0xf3, 0xf3, 0xf9, 0xf9, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
			0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 0xff, 0xff, 0xff, 
			0xff, 0xff, 0xff, 0xc3, 0x81, 0x03, 0x63, 0xf1, 0xe1, 0xe1, 0xe1, 0xe3, 0xe7, 0xe7, 0xef, 0xef
    };

    oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
	}
	#define stack_size 34

	uint16_t calculator_timer = 0;
	uint16_t calculator_counter = 0;


	bool calc_on = false;
	char char_stack[stack_size];
	char temp_char[2];

	bool process_record_user(uint16_t keycode, keyrecord_t *record) {
		if (record->event.pressed && calculator_counter < stack_size) {
			bool invalid_character = false;

			calculator_timer = timer_read();

			uint16_t adjusted_keycode = keycode - 40;
			switch (keycode)
			{
			case KC_PDOT:
				adjusted_keycode = 46;
				break;
			case KC_P0:
				adjusted_keycode = 48;
				break;
			case KC_PENT:
				adjusted_keycode = 61;
				break;
			case KC_PPLS:
				adjusted_keycode = 43;
				break;
			case KC_PMNS:
				adjusted_keycode = 45;
				break;
			case KC_PAST:
				adjusted_keycode = 42;
				break;
			case KC_PSLS:
				adjusted_keycode = 47;
				break;
				default:
					if(keycode < 89 || keycode > 107) {
						calculator_counter = 0;
						adjusted_keycode = 0;
						for (int i = 0; i < stack_size; i++) {
							char_stack[i] = temp_char[1];
						}						invalid_character = true;
					}
					break;
			}
			if(keycode >= 89 || keycode <= 107) {
				sprintf(temp_char, "%c", (adjusted_keycode));
				char_stack[calculator_counter] = temp_char[0];

				char_stack[calculator_counter + 1] = temp_char[1];
				if(!invalid_character) {
					++calculator_counter;
				}
			}
						
				//by default, the keycode doesn't matchup with the actual key pressed. this messes with the numbers so it does.
			
      calc_on = true;
		}
	// 		break;
  // }
	return true;
	};

	void oled_task_user(void) {
		render_image();
		oled_set_cursor(0,8);
		
		switch (get_highest_layer(layer_state)) {
			case _BASE:
				oled_write_P(PSTR("Numbs"), false);
				break;
			case _FN1:
				oled_write_ln_P(PSTR("Gamer"), false);
				break;
			default:
				oled_write_ln_P(PSTR("Undef"), false);
				break;
		}
		switch (calc_on){
			case true:
				for (int i = 0; i < stack_size; i++) {

					oled_write_char(char_stack[i], false);
				}
				if(calculator_counter >= stack_size) {
					oled_write_char('X', false);
				}
			break;
		
		default:
			oled_write_ln_P(PSTR("                              "), false);
			break;
		}
		// Host Keyboard LED Status
		led_t led_state = host_keyboard_led_state();
		if (!led_state.num_lock) {
			register_code(KC_NUMLOCK);
			unregister_code(KC_NUMLOCK);
		}
		void timed_events(void) {
			if(timer_elapsed(calculator_timer) > 2000) {
				calc_on = false;
				calculator_counter = 0;
				for (int i = 0; i < stack_size; i++) {
					char_stack[i] = temp_char[1];
				}
			}
		} 
		timed_events();
	}
#endif
