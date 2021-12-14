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
#define stack_size 44
#define _SVID_SOURCE
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avr_f64.h"
// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE,
  _FN1
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                  KC_MPRV,   KC_MPLY,   KC_MNXT,   TG(_FN1),
				          KC_ESC, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_BSPC, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_COMM,  KC_P0,   KC_P0,   KC_PDOT, KC_PENT,
		
				          KC_F5,   KC_F6,   KC_F7

    ),
    [_FN1] = LAYOUT(
                 KC_MPRV,   KC_MPLY,   KC_MNXT,  _______,
                 _______,  _______, _______, _______,
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        _______, RGB_RMOD, RGB_TOG, RGB_MOD, _______,
        _______, RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_SAD,  _______, RGB_SAI, _______,

                 _______, _______, _______

    )
};


void led_set_keymap(uint8_t usb_led) {
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

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
	static void render_image(int index) {
		if(index == 0) {
			static const char PROGMEM qmk_logo[] = {
				// 'idso1kjm4im51', 32x128px
				0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 
				0xf8, 0xfc, 0xf8, 0xe0, 0xc0, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0xe0, 0x60, 0x23, 0x43, 0x03, 0x07, 0x07, 0x7f, 0xff, 0xfe, 0xfc, 0xe0, 0xe0, 0xe1, 0x81, 
				0x00, 0x00, 0x00, 0x98, 0x08, 0x08, 0x0c, 0x0c, 0x18, 0x18, 0xb8, 0x38, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0xc0, 0xfc, 0xf6, 0xf6, 0xf0, 0xe0, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
				0xfc, 0xfc, 0xfd, 0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x03, 0x1f, 0x7f, 0xff, 0xff, 0xf9, 0xf1, 0xf1, 0xf1, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xe0, 
				0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x3f, 0xf0, 0xe0, 0xc0, 0xd0, 0xd8, 0xd8, 0xf8, 0xf9, 0xf9, 
				0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 
				0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};
    oled_write_raw_P(qmk_logo, sizeof(qmk_logo));

		} else {
			
		oled_write_ln_P(PSTR(":)                                                                            "), false);
		}//todo make this match up with the keymap. make the keymap worth using.
	}

void double_to_char(double f, char * buffer){
    sprintf(buffer, "%f", f);
}

void morphNumericString (char *s, int n) {
    char *p;
    int count;

    p = strchr (s,'.');         // Find decimal point, if any.
    if (p != NULL) {
        count = n;              // Adjust for more or less decimals.
        while (count >= 0) {    // Maximum decimals allowed.
             count--;
             if (*p == '\0')    // If there's less than desired.
                 break;
             p++;               // Next character.
        }

        *p-- = '\0';            // Truncate string.
        while (*p == '0')       // Remove trailing zeros.
            *p-- = '\0';

        if (*p == '.') {        // If all decimals were zeros, remove ".".
            *p = '\0';
        }
    }
	}

	//requires a string that only contains numbers and dots, probably
	// int decimalCount (char *s) {
	// 		morphNumericString(s, stack_size);
	// 		int finalCount = 0;
	// 		bool hasDecimal = false;
	// 		//iterates over characters in reverse order.
	// 		for(int i=strlen(s); i; i--) {
	// 				char current_char = s[i-1];
	// 				if(current_char >= '0' && current_char <= '9') {
	// 						finalCount++;
	// 				} else if(current_char == '.') {
	// 						hasDecimal = true;
	// 						break;
	// 				}
	// 		}
	// 		if(!hasDecimal) {
	// 				finalCount = 0;
	// 		}
	// 		return(finalCount);
	// }

	// void removeDecimal(char *s) {
	// 		morphNumericString(s, stack_size);
	// 		char tempString[stack_size]; 
	// 		int index = 0;
	// 		for(unsigned int i=0; i < strlen(s); i++) {
	// 				if(s[i] != '.'){
	// 						tempString[index] = s[i];
	// 						tempString[index + 1] = '\0';
	// 						index++;
	// 				}
	// 		}
	// 		strcpy(s, tempString);
	// }

	// void addZeroes(char *s, int number) {
	// 		int index = strlen(s);
	// 		for(int i = 0; i < number; i++) {
	// 				s[index] = '0';
	// 				s[index + 1] = '\0';
	// 				index++;
	// 		}
	// }

	// void addDecimal(char *s, int decimals) {
	// 	morphNumericString(s, 100);
	// 	if(decimals > 0) {
	// 		char tempString[stack_size];
	// 		int index = 0;
	// 		if(strlen(s) > decimals) {
	// 			int insertionPoint = strlen(s) - decimals;
	// 			for(unsigned int i=0; i < strlen(s); i++) {
	// 				tempString[index] = s[i];
	// 				index++;
	// 				if(i == insertionPoint - 1){
	// 					tempString[index] = '.';
	// 					index++;
	// 				}
	// 			}
	// 		} else {
	// 			strcpy(tempString, "0.");
	// 			addZeroes(tempString, decimals - strlen(s));
	// 			strcat(tempString, s);
	// 		}
	// 		strcpy(s, tempString);
	// 	}
					
	// }

	uint16_t calculator_timer = 0;
	uint16_t calculator_counter = 0;

	char *nullptr;
	bool calc_on = false;
	char char_stack[stack_size];
	char temp_char[2] = "0";
	bool has_operator = false;
	bool dont_allow_decimals = false;
	bool dont_allow_minus = false;
	int decimal_count = 0;
	int minus_count = 0;
	char chosen_operator[2] = {0};
	bool answer_exists = false;
	//make sure that pressing enter on empty strings and etc works fine

	void clear_calc(void) {
		calculator_counter = 0;
		decimal_count = 0;
		minus_count = 0;
		has_operator = false;
		dont_allow_decimals = false;
		dont_allow_minus = false;
		answer_exists = false;
		chosen_operator[0] = '\0';
		memset(char_stack, '\0', sizeof char_stack);
	}

	bool process_record_user(uint16_t keycode, keyrecord_t *record) {
		if (record->event.pressed) {
			bool invalid_character = false;
			calculator_timer = timer_read();
			uint16_t adjusted_keycode = keycode - 40;


			int getOperatorIndex (void) {
				int tempIndex = 0;
				for(int i = 1; i < strlen(char_stack); i++) {
					if(char_stack[i] == chosen_operator[0]) {
						tempIndex = i;
						break;
					}
				}
				return tempIndex;
			}
			void check_for_operator(char op) {
				if (has_operator == true) {
					invalid_character = true;
					for (int i = 0; i < stack_size; i++) {
						if(char_stack[i] == chosen_operator[0]) {
							char_stack[i] = op;
							chosen_operator[0] = op;
							break;
						}
					}
				} else if (calculator_counter > 0) {

					//if an operator is added, re allow decimals to be inputted
					adjusted_keycode = op;
					dont_allow_decimals = false;
					has_operator = true;
					chosen_operator[0] = op;
				} else {
					invalid_character = true;
				}
			}
			void check_for_decimals(void) {
				if (dont_allow_decimals == true) {
					invalid_character = true;
				} else {
					if(has_operator && decimal_count < 2) {	
							dont_allow_decimals = true;
						++decimal_count;
					} else if (!has_operator && decimal_count < 1) {
						dont_allow_decimals = true;
						++decimal_count;
					} else {
						invalid_character = true;
					} 
				}
			}
			void check_for_minus(void) {
				void addMinus(void) {
					++minus_count;
				}
				if(has_operator == false) {
					if(//Written as X = invalid locations O = valid location.
						strlen(char_stack) == 0//O
					) {
						addMinus();
					} else if ((strlen(char_stack) >= 2 && minus_count == 1)||(strlen(char_stack) >= 1 && minus_count == 0)) {//-XOOO...//XOOO...
						check_for_operator('-'); //add minus as operator
						addMinus();
					} else {
						invalid_character = true;
					}
				} else {//if it has an operator
				int operatorIndex = getOperatorIndex();
				if(operatorIndex == calculator_counter - 1) {
					addMinus();
				} else {
					invalid_character = true;
				}
				}
			}

			switch (keycode)
			{
			case KC_P0:
				adjusted_keycode = '0';
				break;
			case KC_PDOT:
				adjusted_keycode = '.';
				check_for_decimals();
				break;
			case KC_PMNS:
				adjusted_keycode = '-';
				check_for_minus();
				break;
			case KC_PPLS:
				check_for_operator('+');
				break;
			case KC_PAST:
				check_for_operator('*');
				break;
			case KC_PSLS:
				check_for_operator('/');
				break;
			case KC_PENT:
				adjusted_keycode = '=';
				break;
			case KC_BSPC: 
				if (strlen(char_stack) >= 1) {
					switch (char_stack[strlen(char_stack) - 1])
					{
					case '.':
						decimal_count--;
						break;
					case '-':
						minus_count--;
						break;
					case '+':
					case '/':
					case '*':
						has_operator = false;
						break;

					}
					char_stack[strlen(char_stack) - 1] = '\0';
					calculator_counter--;
				}
				invalid_character = true;
				break;
			default:
				//if the keycode is outside of the range of numbers 1-9
				if(keycode < 89 || keycode > 107) {
					//reset the calculator
					clear_calc();
					invalid_character = true;
				}
				break;
			}
			if(!invalid_character && adjusted_keycode != '=' && calculator_counter < stack_size) {
				if(has_operator != answer_exists && answer_exists) {//if it doesn't have an operator, but does have an answer. makes it so that typing numbers clears the calculator, but typing operators uses the existing answer.
					clear_calc();
				} else {
					answer_exists = false;
				}
				//edit a temporary string to hold the character just inputted
				sprintf(temp_char, "%c", (adjusted_keycode));
				//edit the character stack to include the new character and a termination character.


				char_stack[calculator_counter] = temp_char[0];
				char_stack[calculator_counter + 1] = temp_char[1];
				if(!invalid_character) {
					++calculator_counter;
				}
			} else if(adjusted_keycode == '=') {
				char temp_math_string[stack_size];
				// int decimals[] = {0, 0};
				float64_t operands[] = {0, 0};
				int operator_index = getOperatorIndex();
				// fills temp math string with the first operator
				void parseOperand(int index) {
					strncpy(temp_math_string,
						char_stack + ((index == 0) ? 0 : operator_index + 1),
						((index == 0) ? operator_index : sizeof char_stack - operator_index)
					);
					temp_math_string[((index == 0) ? operator_index : sizeof char_stack - operator_index)] = '\0';

					// decimals[index] = decimalCount(temp_math_string);

					// removeDecimal(temp_math_string);
					if(index == 0) {
						operands[0] = f_strtod(temp_math_string, &nullptr);
					} else {
						operands[1] = f_strtod(temp_math_string, &nullptr);
					}
				}


				//todo ensure that bad requests like empty operands are handled gracefully
				parseOperand(0);
				parseOperand(1);
				// uint16_t greaterDecimals = 0;
				// if(decimals[0] < decimals[1]) greaterDecimals = 1;
				// uint16_t decimalDiff = decimals[greaterDecimals] - decimals[1 - greaterDecimals];


				switch (chosen_operator[0])
				{//todo make sure it's limited by long int size limits
				case '+':
					operands[0] = f_add(operands[0], operands[1]);
					break;
				case '-':
					// for (int i = 0; i < decimalDiff; i++) {
					// 	operands[1 - decimalDiff] = f_mult(operands[1 - decimalDiff], ten);
					// }
					// 	// f_mult(operands[1], 100);
					// 	// operands[0] = f_long_to_float64(10);
					// //run as many times as the difference between decimals is.
					operands[0] = f_sub(operands[0], operands[1]);
					break;
				case '*':
					operands[0] = f_mult(operands[0], operands[1]);
					break;
				case '/':
					operands[0] = f_div(operands[0], operands[1]);
					break;
				}
				strcpy(temp_math_string, f_to_string(operands[0], stack_size - 1, 2));
				temp_math_string[strlen(temp_math_string)] = '\0';
				clear_calc();
				strcpy(char_stack, temp_math_string);
				morphNumericString(char_stack, stack_size);
				calculator_counter = strlen(char_stack);
				answer_exists = true;
				//todo does not account for the presence of decimals
			}//todo increase accuracy by making things into ints and then back into doubles
				//by default, the keycode doesn't matchup with the actual key pressed. this messes with the numbers so it does.
      calc_on = true;
		}
	// 		break;
  // }
	return true;
	};

	void oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
			case _BASE:
				render_image(0);
				oled_set_cursor(0,6);

				switch (calc_on) {
					case true:
						for (int i = 0; i < stack_size; i++) {

							oled_write_char(char_stack[i], false);
						}
						if(calculator_counter >= stack_size) {
							oled_write_char('X', false);
						}
					break;
				
				default:
					oled_write_ln_P(PSTR("                                        "), false);
					break;
				}
          break;
      case _FN1:
				render_image(1);
				break;
		}
		
		//todo make it so that the different states display correctly. Perhaps set it up so that each state has its own image.
		void timed_events(void) {
			if(timer_elapsed(calculator_timer) > 30000) {
				calc_on = false;
				clear_calc();
			}
		} 
		timed_events();
	}
#endif
