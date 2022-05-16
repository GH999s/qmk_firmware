/*  MiKiBordV3a, tT, 2022, multi editors macro keyboard */

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "quantum.h"

// 224x64
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0, 1, 2, NO_LED },
  { 5, 4, 3, NO_LED },
}, {
  // LED Index to Physical Position
    { 0, 0}, { 112, 0}, { 224,0 },
    { 224, 64}, { 112,64 }, { 0, 64},
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4
} };


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
float   rgb_RE_position   = 0;
bool    RE_action_flag    = false;

#define ____ KC_TRNS

//  Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L,
        KC_M, KC_N, KC_O, KC_P
    ),
    [1] = LAYOUT(
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____
    ),
    [2] = LAYOUT(
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____    
    ),
    [3] = LAYOUT(
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____,
        ____, ____, ____, ____
    ),
/*  KEY DEFINITIONS:
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
    if (RE_action_flag == true) {
        if (timer_elapsed(rgblight_key_time) > 1000) {
            rgblight_set_effect_range(0, RGBLED_NUM);
            rgblight_mode_noeeprom(rgblight_oldmode);
            RE_action_flag=false;
        }
    }
}

void encoder_rgb_animation(void) {
    rgblight_key_time = timer_read();
    if (rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT){
        rgblight_oldmode=rgblight_get_mode();
    }
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_range(5, 5, 25, 0, RGBLED_NUM);     // <- Blau  (25,25,25,0 weiss)  Set Background Color on turning REs
    rgblight_setrgb_at(80, 0, 0, rgb_RE_position);         // <- Rot                       Set Current Position of REs (Red)
    RE_action_flag = true;
}

void RGB_RE_position(void) {    // Rotary Encoder Counter minus
    if      (rgb_RE_position>(RGBLED_NUM-1))   { rgb_RE_position= -1; }  // CCW  Minus 0 -> 16, OK, Leerschritt im 0-Übergang
    else if (rgb_RE_position<0)                { rgb_RE_position= 16; }  //  CW   Plus 16 -> 0, Leerschritt im 0-Übergang
}

void RGB_RE_position_plus(void) {     // Rotary Encoder Counter plus
    rgb_RE_position+=1;
}

void RGB_RE_position_minus(void) {    // Rotary Encoder Counter minus
    rgb_RE_position-=1;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    RGB_RE_position();

/*
    switch (index) { // RE No.
        case 0: 
            switch (Layer No.) { 
                case 0: 
                    switch: clockwise {
                        case 1:
                            tap_code(RE1AL0);
                            RGB_RE_position_plus();
                            break;
                        default:
                            tap_code(RE1BL0);
                            RGB_RE_position_minus();
                            break;
                    }    
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
            }

        case 1: 
                break;
        case 2:
                break;
        case 3:
                break;
        default:
                break;
    }
*/
    encoder_rgb_animation();
    if (index == 0) { //    RE1 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE1AL0);
                RGB_RE_position_plus();
            } else {
                tap_code(RE1BL0);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE1AL1);
                RGB_RE_position_plus();
            } else {
                tap_code(RE1BL1);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE1AL2);
                RGB_RE_position_plus();
            } else {
                tap_code(RE1BL2);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE1AL3);
                RGB_RE_position_plus();
            } else {
                tap_code(RE1BL3);
                RGB_RE_position_minus();
            }
        }
        //encoder_rgb_animation();
    }
    if (index == 1) { //    RE2 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE2AL0);
                RGB_RE_position_plus();
            } else {
                tap_code(RE2BL0);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE2AL1);
                RGB_RE_position_plus();
            } else {
                tap_code(RE2BL1);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE2AL2);
                RGB_RE_position_plus();
            } else {
                tap_code(RE2BL2);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE2AL3);
                RGB_RE_position_plus();
            } else {
                tap_code(RE2BL3);
                RGB_RE_position_minus();
            }
        }
        //encoder_rgb_animation();
    }
    if (index == 2) { //    RE3 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE3AL0);
                RGB_RE_position_plus();
            } else {
                tap_code(RE3BL0);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE3AL1);
                RGB_RE_position_plus();
            } else {
                tap_code(RE3BL1);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE3AL2);
                RGB_RE_position_plus();
            } else {
                tap_code(RE3BL2);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE3AL3);
                RGB_RE_position_plus();
            } else {
                tap_code(RE3BL3);
                RGB_RE_position_minus();
            }
        }
        //encoder_rgb_animation();
    }
    if (index == 3) { //    RE4 A/B
        if(IS_LAYER_ON(0)){
            if (clockwise) {
                tap_code(RE4AL0);
                RGB_RE_position_plus();
            } else {
                tap_code(RE4BL0);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(1)){ 
            if (clockwise) {
                tap_code(RE4AL1);
                RGB_RE_position_plus();
            } else {
                tap_code(RE4BL1);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(2)){
            if (clockwise) {
                tap_code(RE4AL2);
                RGB_RE_position_plus();
            } else {
                tap_code(RE4BL2);
                RGB_RE_position_minus();
            }
        }
        if(IS_LAYER_ON(3)){
            if (clockwise) {
                tap_code(RE4AL3);
                RGB_RE_position_plus();
            } else {
                tap_code(RE4BL3);
                RGB_RE_position_minus();
            }
        }
        //encoder_rgb_animation();
    }
return true;    
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const int led_index = 2;
    switch(get_highest_layer(layer_state)) {
        case 1:
            rgb_matrix_set_color(led_index, RGB_WHITE);
            break;
        case 2:
            rgb_matrix_set_color(led_index, RGB_BLUE);
            break;
        case 3:
            rgb_matrix_set_color(led_index, RGB_GREEN);
            break;
        default:
            break;
    }
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    if(data[0] == 0xFC){
        switch (data[1]) {
            case 0x01:{
                // move to layer
                data[1] = 0xFD;
                layer_move(data[2]);
                break;
            }
            case 0x02:{
                // turn on layer
                data[1] = 0xFD;
                layer_on(data[2]);
                break;
            }
            case 0x03:{
                // turn off layer
                data[1] = 0xFD;
                layer_off(data[2]);
                break;
            }
        }
    }
    raw_hid_send(data, length);
}


