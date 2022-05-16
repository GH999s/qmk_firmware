/*  MiKiBordV3a, tT, 2022, multi editors macro keyboard */

#pragma once

#include "config_common.h"

#define VIAL_KEYBOARD_UID {0x49, 0xC9, 0x93, 0xD6, 0x37, 0xB5, 0xDB, 0xDC} // tT
#define VENDOR_ID    0X2341     //  dez 9025    // 0xFEED (VID)
#define PRODUCT_ID   0X8036     //  dez 32822   // 0x0000 (PID)
#define DEVICE_VER   0x0001
#define MANUFACTURER tT
#define PRODUCT      MiKiBordV3a
#define DESCRIPTION  multi editors macro keyboard

// KEY MATRIX
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
#define MATRIX_COL_PINS { D7, E6, B4, B5 }
//  #define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B2, B1, F6, F4 }
#define ENCODERS_PAD_B { B6, B3, F7, F5 }
#define VIAL_ENCODER_DEFAULT { KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }
#define ENCODER_DIRECTION_FLIP { 0, 1, 1, 1 }
//  #define ENCODER_RESOLUTION 1
#define ENCODER_RESOLUTIONS { 4, 4, 4, 4 }
// ?????????????????????????????????????????????????????????????????????????
#define VIAL_UNLOCK_COMBO_ROWS { 1, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
#define DEBOUNCE 5 

//  RGBCONFIG
//  Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
//  #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

//  #define LED_NUM_LOCK_PIN B0
//  #define LED_CAPS_LOCK_PIN B1
//  #define LED_SCROLL_LOCK_PIN B2
//  #define LED_COMPOSE_PIN B3
//  #define LED_KANA_PIN B4

//  #define BACKLIGHT_PIN B7
//  #define BACKLIGHT_LEVELS 3
//  #define BACKLIGHT_BREATHING

#define  RGB_DI_PIN D3
#define  RGBLED_NUM 16          // ANZAHL LEDs
// wlard
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES


// wlard ausgeschaltet
/*
#define  RGBLIGHT_HUE_STEP 8
#define  RGBLIGHT_SAT_STEP 32
#define  RGBLIGHT_VAL_STEP 32
#define  RGBLIGHT_LIMIT_VAL 255  // The maximum brightness level 
//  #define RGBLIGHT_SLEEP       // If defined, the RGB lighting will be switched off when the host goes to sleep 
//  == all animations enable ==
#define RGBLIGHT_ANIMATIONS
//  == or choose animations ==
//  #define RGBLIGHT_EFFECT_BREATHING
//  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL 2
//  #define RGBLIGHT_EFFECT_SNAKE
//  #define RGBLIGHT_EFFECT_KNIGHT
//  #define RGBLIGHT_EFFECT_CHRISTMAS
//  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//  #define RGBLIGHT_EFFECT_RGB_TEST
//  #define RGBLIGHT_EFFECT_ALTERNATING
//  ==== customize breathing effect ====
//  ==== (DEFAULT) use fixed table instead of exp() and sin() ====
//  #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//  ==== use exp() and sin() ====
//  #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//  #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255

//  define if matrix has ghost (lacks anti-ghosting diodes)
//  #define MATRIX_HAS_GHOST

//  Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
//  Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

//  If defined, GRAVE_ESC will always act as ESC when CTRL is held.
//  This is useful for the Windows task manager shortcut (ctrl+shift+esc).

//  #define GRAVE_ESC_CTRL_OVERRIDE

//  Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
//  state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
//  makefile for this to work.)
//  If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
//  until the next keyboard reset.
//  NKRO may prevent your keystrokes from being detected in the BIOS, but it is
//  fully operational during normal computer usage.
//  For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
//  or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
//  bootmagic, NKRO mode will always be enabled until it is toggled again during a
//  power-up.
//  #define FORCE_NKRO


//  Feature disable options
//  These options are also useful to firmware size reduction.

//  disable debug print
//  #define NO_DEBUG

//  disable print
//  #define NO_PRINT

//  disable action features
//  #define NO_ACTION_LAYER
//  #define NO_ACTION_TAPPING
//  #define NO_ACTION_ONESHOT

//  disable these deprecated features by default
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//  Bootmagic Lite key configuration
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

*/