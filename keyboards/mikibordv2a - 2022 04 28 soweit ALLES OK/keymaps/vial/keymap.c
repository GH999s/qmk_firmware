/*  MiKiBordV2a, 2022, multi editors macro keyboard

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
#include "raw_hid.h"
#include "quantum.h"

//  RE (Rotary Encoder) Base Function Definitions
//  Layer 0
#define RE1AL0 KC_KP_1
#define RE1BL0 KC_KP_2
#define RE2AL0 KC_KP_3
#define RE2BL0 KC_KP_4
#define RE3AL0 KC_VOLD
#define RE3BL0 KC_VOLU
#define RE4AL0 KC_BRID
#define RE4BL0 KC_BRIU
//  Layer 1
#define RE1AL1 KC_A
#define RE1BL1 KC_B
#define RE2AL1 KC_C
#define RE2BL1 KC_D
#define RE3AL1 KC_VOLD
#define RE3BL1 KC_VOLU
#define RE4AL1 KC_BRID
#define RE4BL1 KC_BRIU
//  Layer 2
#define RE1AL2 KC_I
#define RE1BL2 KC_J
#define RE2AL2 KC_K
#define RE2BL2 KC_L
#define RE3AL2 KC_VOLD
#define RE3BL2 KC_VOLU
#define RE4AL2 KC_BRID
#define RE4BL2 KC_BRIU
//  Layer 3
#define RE1AL3 KC_A
#define RE1BL3 KC_B
#define RE2AL3 KC_C
#define RE2BL3 KC_D
#define RE3AL3 KC_VOLD
#define RE3BL3 KC_VOLU
#define RE4AL3 KC_BRID
#define RE4BL3 KC_BRIU

//  LED Variables
float   enco_counter    = 0;
bool    encoder_flag    = false;

//  Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TO(1), KC_A, KC_B, KC_C,
        KC_D,  KC_E, KC_F, KC_G,
        KC_H,  KC_I, KC_J, KC_K,
        KC_L,  KC_M, KC_N, KC_O
    ),
    [1] = LAYOUT(
        TO(2),   KC_KP_1, KC_KP_2, KC_KP_3,
        KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7,
        KC_BRID, KC_BRIU, KC_KP_8, KC_KP_9, 
        KC_VOLD, KC_VOLU, KC_KP_MINUS, KC_KP_PLUS 
    ),
    [2] = LAYOUT(
        TO(3), KC_P, KC_Q, KC_R,
        KC_S,  KC_T, KC_U, KC_V,
        KC_W,  KC_X, KC_Y, KC_Z,
        KC_A,  KC_B, KC_C, KC_D
    ),
    [3] = LAYOUT(
        TO(0),   RGB_TOG, RGB_MOD, RGB_RMOD,
        RGB_HUD, RGB_HUI, _______, _______, 
        RGB_SAD, RGB_SAI, _______, _______, 
        RGB_VAD, RGB_VAI, _______, _______
    ),
/*  USEFUL KEY DEFINITIONS
    TO(X), MO(X), 
    RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, 
    RGB_SPD, RGB_SPI, 
    KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_FIND, 
    KC_BRID, KC_BRIU, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY, 
    KC_MS_D, KC_MS_U, KC_MS_L, KC_MS_R, KC_BTN1 ... KC_BTN5, KC_WH_D, KC_WH_U, KC_WH_L, KC_WH_R      
    (ProgLaunch)
    KC_CALC, KC_MAIL, KC_MSEL, KC_MYCM
    KC_F23, KC_TRNS, _______, 
    KC_A, KC_KP_1, 

    [1] = LAYOUT(
        _______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______
    ),
*/
};
/*
void keyboard_post_init_user(void) {                        // Call the post init code.
//  rgblight_enable_noeeprom();                             // enables Rgb, without saving settings
//  rgblight_sethsv_noeeprom(60, 60, 60);                   // sets the color to teal/cyan without saving
//  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);    // sets mode to Fast breathing without saving
}
*/
static uint16_t rgblight_key_time;
static uint32_t rgblight_oldmode;

void matrix_scan_user(void) {
    if (encoder_flag == true) {
        if (timer_elapsed(rgblight_key_time) > 1000) {
            rgblight_set_effect_range(0, RGBLED_NUM);
            rgblight_mode_noeeprom(rgblight_oldmode);
            encoder_flag=false;
        }
    }
}

void encoder_rgb_animation(void) {
    rgblight_key_time = timer_read();
    if (rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT){
        rgblight_oldmode=rgblight_get_mode();
    }
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_range(5, 5, 25, 0, RGBLED_NUM);         // <- Blau  (25,25,25,0 weiss)  // 80, 80, 80, 0 ORIG   Set Background Color on turning REs
    rgblight_setrgb_at(80, 0, 0, enco_counter /*abs(round(enco_counter))*/); // <- Rot                       // 180, 0, 0 ORIG       Set Current Position of REs (Red)
    encoder_flag = true;
}

void RGB_enco_counter_check(void) {    // Rotary Encoder Counter minus
/* Funktiomiert beide Richtungen, hat im Nulldurchgang beide Richtungen 1 Schritt zuviel
    if      (enco_counter>(RGBLED_NUM-1))   { enco_counter = -1; }  // CCW  Minus 0 -> 16
    else if (enco_counter<0)                { enco_counter = 16; }   // CW   Plus 16 -> 0
*/
    if      (enco_counter>(RGBLED_NUM-1))   { enco_counter = -1; }  // CCW  Minus 0 -> 16       OK, Leerschritt im 0-Übergang
    else if (enco_counter<0)                { enco_counter = 16; }   // CW   Plus 16 -> 0       OK, Leerschritt im 0-Übergang
}

void RGB_REplus(void) {     // Rotary Encoder Counter plus
    enco_counter+=1;
}

void RGB_REminus(void) {    // Rotary Encoder Counter minus
    enco_counter-=1;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
//    if (abs(enco_counter) >= RGBLED_NUM-1) {
/*
    if (enco_counter >= RGBLED_NUM) { // -1
        enco_counter = 0;
    }
    if (enco_counter < 1 ) {
//        enco_counter = RGBLED_NUM-1;
        enco_counter = RGBLED_NUM;    //-1
    }
*/
    RGB_enco_counter_check();

    if (index == 0) { //    RE1 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE1AL0);
                RGB_REplus();
            } else {
                tap_code(RE1BL0);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE1AL1);     // tap_code16() ???
                RGB_REplus();
            } else {
                tap_code(RE1BL1);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE1AL2);
                RGB_REplus();
            } else {
                tap_code(RE1BL2);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE1AL3);
                RGB_REplus();
            } else {
                tap_code(RE1BL3);
                RGB_REminus();
            }
        }
        encoder_rgb_animation();
    }
    if (index == 1) { //    RE2 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE2AL0);
                RGB_REplus();
            } else {
                tap_code(RE2BL0);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE2AL1);
                RGB_REplus();
            } else {
                tap_code(RE2BL1);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE2AL2);
                RGB_REplus();
            } else {
                tap_code(RE2BL2);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE2AL3);
                RGB_REplus();
            } else {
                tap_code(RE2BL3);
                RGB_REminus();
            }
        }
        encoder_rgb_animation();
    }
    if (index == 2) { //    RE3 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE3AL0);
                RGB_REplus();
            } else {
                tap_code(RE3BL0);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE3AL1);
                RGB_REplus();
            } else {
                tap_code(RE3BL1);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE3AL2);
                RGB_REplus();
            } else {
                tap_code(RE3BL2);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE3AL3);
                RGB_REplus();
            } else {
                tap_code(RE3BL3);
                RGB_REminus();
            }
        }
        encoder_rgb_animation();
    }
    if (index == 3) { //    RE4 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE4AL0);
                RGB_REplus();
            } else {
                tap_code(RE4BL0);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE4AL1);
                RGB_REplus();
            } else {
                tap_code(RE4BL1);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE4AL2);
                RGB_REplus();
            } else {
                tap_code(RE4BL2);
                RGB_REminus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE4AL3);
                RGB_REplus();
            } else {
                tap_code(RE4BL3);
                RGB_REminus();
            }
        }
        encoder_rgb_animation();
    }
return true;    
}


