/*  MiKiBordV2a, tT, 2022

    Copyright 2021 AlexF

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

float   enco_counter    = 0;
bool    encoder_flag    = false;

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MO(1), KC_1, KC_2, KC_3,
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L        
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
//  Call the post init code.
//  rgblight_enable_noeeprom();                             // enables Rgb, without saving settings
//  rgblight_sethsv_noeeprom(60, 60, 60);                   // sets the color to teal/cyan without saving
//  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);    // sets mode to Fast breathing without saving
}

static uint16_t key_timer;
static uint32_t oldmode;

void matrix_scan_user(void) {
    if (encoder_flag == true) {
        if (timer_elapsed(key_timer) > 1000) {
            rgblight_set_effect_range(0, RGBLED_NUM);
            rgblight_mode_noeeprom(oldmode);
            encoder_flag=false;
        }
    }
}

void encoder_rgb_animation(void) {
    key_timer = timer_read();
    if (rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT){
        oldmode=rgblight_get_mode();
    }
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_range(80, 80, 80, 0, RGBLED_NUM);           //turn beginning colored
    rgblight_setrgb_at(180, 0, 0, abs(round(enco_counter)));    //set current red
    encoder_flag = true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (abs(enco_counter) >= RGBLED_NUM-1) {
        enco_counter = 0;
    }
    if (enco_counter <0 ) {
        enco_counter = RGBLED_NUM-1;
    }
    if (index == 0) { // RE1 A/B
        if(IS_LAYER_ON(0)||IS_LAYER_ON(4)){
            if (clockwise) {
                tap_code(KC_LEFT);
                enco_counter=enco_counter+0.05;
                encoder_rgb_animation();
                //rgblight_step();

            } else {
                tap_code(KC_RGHT);
                enco_counter=enco_counter-0.05;
                encoder_rgb_animation();
                //rgblight_step_reverse();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code16(S(KC_LEFT));
                enco_counter=enco_counter+1;
                encoder_rgb_animation();
                //rgblight_step();

            } else {
                tap_code16(S(KC_RGHT));
                enco_counter=enco_counter-1;
                encoder_rgb_animation();
                //rgblight_step_reverse();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(KC_UP);
                enco_counter=enco_counter+0.6;
                encoder_rgb_animation();
                //rgblight_step();

            } else {
                tap_code(KC_DOWN);
                enco_counter=enco_counter-0.6;
                encoder_rgb_animation();
                //rgblight_step_reverse();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code16(C(KC_Y));
                enco_counter=enco_counter+0.6;
                encoder_rgb_animation();
                //rgblight_step();

            } else {
                tap_code16(C(S(KC_Y)));
                enco_counter=enco_counter-0.6;
                encoder_rgb_animation();
                //rgblight_step_reverse();
            }
        }
    }
return true;    
}

