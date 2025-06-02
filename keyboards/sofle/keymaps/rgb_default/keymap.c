
 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any...ater version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  // SOFLE RGB
#include <stdio.h>
#include "features/caps_word.h"

#include QMK_KEYBOARD_H

#ifdef PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#include "ps2.h"
#endif

int layout;

#define LAT 0
#define RUS 1

//#define ENCODER_RESOLUTION 4

#define INDICATOR_BRIGHTNESS 150

#define IS_MAC keymap_config.swap_lctl_lgui
#define LAYER_LOCK_KEY MOD_MASK_CTRL

#define KC_LGUI_X LM(_COLEMAKDH, MOD_LGUI)
#define KC_LALT_X LM(_COLEMAKDH, MOD_LALT)
#define KC_LCTL_X LM(_COLEMAKDH, MOD_LCTL)

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}

#define SET_LAYER_ID_CUSTOM(hsv, brightness) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, brightness)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, brightness)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _COLEMAK,
    _COLEMAKDH,
    _SOFTWARE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD    
};

enum custom_keycodes {
    KC_RUS = SAFE_RANGE,
    KC_LAT,
	KC_COLEMAKDH,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_D_MUTE,
    KC_WM_UNDO,
    KC_LEND,
    KC_LSTRT,
    KC_DSTRT,
    KC_DEND,
    KC_WM_CUT, 
    KC_WM_COPY, 
    KC_WM_PASTE,
    KC_LANG,
    ALT_TAB,
    U_DOLLAR,
    U_SCLN,
    U_MORE,
    U_LESS, 
    U_CLR,
    U_CSQRT,
    U_OSQRT,
    U_QUOT,
    U_P_VAL,
    U_P_FMT,
    U_P_FRM,
    KC_DESK,
    KC_SHORT,
    KC_WSTRT,
    KC_WEND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  LT(_NUMPAD,KC_ESC),KC_1,  KC_2,    KC_3,    KC_4,  KC_5,                  KC_6,  KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,   KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN,    KC_LBRC, // allows Russian letter X
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    LT(0, KC_GRV),  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,               KC_H,    KC_N,   KC_E,    KC_I,   KC_O,  KC_QUOT, // allows Russian letter Э
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  CG_TOGG,  TG(_SOFTWARE),  KC_K,LT(0, KC_M),KC_COMM, KC_DOT,  LT(0,KC_SLSH), KC_RUS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_LCTL_X, KC_LALT_X, KC_LGUI_X, KC_LSFT,  MO(_LOWER),    MO(_RAISE),   LT(0,KC_SPC),  KC_LCTL_X, KC_DEL, KC_ENT
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_COLEMAK] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  LT(_NUMPAD,KC_ESC),KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_TRNS,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,      KC_TRNS,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,    KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
 KC_TRNS,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_TRNS,    KC_TRNS,KC_N,LT(0, KC_M),   KC_TRNS, KC_TRNS,  KC_TRNS, KC_LAT,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  MO(_LOWER),    MO(_RAISE), KC_TRNS,  KC_LCTL_X, KC_TRNS, KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/*
 * COLEMAK-DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_COLEMAKDH] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  KC_TRNS,  KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_F5,                 KC_F6,    KC_F7,   KC_F8,    KC_F9,    KC_F10,    KC_F11,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_F12,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,   KC_E,    KC_I,    KC_O,    KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_TRNS,   KC_TRNS, KC_K,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  //,------------------------------------------------.                                      ,---------------------------------------------------.
  _______,KC_F1,  KC_F2, KC_F3, KC_F4,   KC_F5,                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|------+-------+--------+--------+--------+------|                                     |--------+-------+--------+--------+--------+---------|
  KC_NO, U_CLR, C(KC_H), U_P_FMT, U_P_VAL, C(A(KC_V)),                                      KC_DSTRT, KC_LSTRT, KC_UP,  KC_LEND, C(KC_UP),   KC_F12,
  //|------+-------+--------+--------+--------+------|                                     |--------+-------+--------+--------+--------+---------|
  _______,ALT_TAB, KC_WM_CUT, KC_WM_COPY, KC_WM_PASTE, KC_LSFT,                             KC_DEND, KC_LEFT, KC_DOWN,  KC_RGHT, C(KC_DOWN),   _______,
  //|------+------+--------+--------+--------+------|  ===  |   |  ===                     |--------+-------+--------+--------+--------+---------|
  _______,KC_WM_UNDO, C(KC_R), C(KC_D), C(KC_MINS), C(KC_PLUS),   _______,    _______,      CG_TOGG, KC_WSTRT,KC_ENT,KC_WEND,  KC_BSPC,  _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,                                _______, KC_ENT, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
 LT(_NUMPAD,KC_ESC),KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_TRNS,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,KC_TILD,  KC_LCBR,   KC_RCBR,  KC_PAST, KC_PSLS,                S(KC_7), U_QUOT, U_LESS,  U_MORE, _______, _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,KC_PIPE,  KC_LPRN,  KC_RPRN,  KC_MINS, KC_PLUS,                   U_DOLLAR, KC_EQL, KC_LPRN,  KC_RPRN, U_SCLN, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,KC_BSLS, KC_LBRC, KC_RBRC, KC_UNDS, KC_EQL,_______,    _______,_______, _______,_______, _______, KC_SLSH, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, RESET
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGB_TOG|hue^ |sat ^ | bri ^|      |COLEMAK|-------.   ,-------|desk <|      |      |desk >|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | mode | hue dn|sat d|bri dn|      |QWERTY|-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  RESET,   XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  RGB_TOG, RGB_HUI,RGB_SAI, RGB_VAI, KC_COLEMAKDH,KC_LAT,             C(G(KC_LEFT)),KC_NO,KC_NO,C(G(KC_RGHT)),XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  RGB_MOD, RGB_HUD,RGB_SAD, RGB_VAD, XXXXXXX,KC_RUS,XXXXXXX,   XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|      |      |      |      |      |                    |      |NumLck|      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |                    |   ^  |   7  |   8  |   9  |   *  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|   -  |   4  |   5  |   6  |      |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NUMPAD] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_TAB, XXXXXXX, KC_ENT, KC_PSLS, KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P7,  KC_P8,   KC_P9,   KC_PAST, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P4,  KC_P5,   KC_P6,   KC_PMNS,  XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,   _______,XXXXXXX, KC_P1,  KC_P2,   KC_P3,   KC_PPLS,   XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
              _______, OSM(MOD_MEH), _______, _______, _______,   _______, _______,  KC_P0, KC_PDOT, KC_ENT
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* SWITCH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | qwer | cole |col_dh| low  | raise| adj  |                    |numpad|      |      |      |      |RESET |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |EEP_RST|
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | SLEEP|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  // layer switcher
[_SOFTWARE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
_______,KC_1,  KC_2,    KC_3,    KC_4,    KC_5,             KC_6, KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_X, KC_W,  KC_U,   KC_SCLN,  KC_NO,                      MI_C,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,   KC_A, KC_F,   KC_B,   KC_K,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EEP_RST,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_Z,  KC_M,    KC_C,  KC_V,   KC_H,  _______,    TG(_SOFTWARE),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TG(_SOFTWARE),
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
         KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT,  KC_LOWER,             KC_TRNS,   KC_SPC,  KC_RALT, KC_DEL, KC_ENT
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/

	),
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID_CUSTOM(HSV_OFF,0)
  //SET_INDICATORS(HSV_GOLD)

);
const rgblight_segment_t PROGMEM layer_colemak_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID_CUSTOM(HSV_PURPLE,50)
  //SET_LAYER_ID_CUSTOM(HSV_OFF)
);

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_GREEN)

);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_TEAL)

    );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
	SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
    );
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID_CUSTOM(HSV_RED,10),
	SET_NUMROW(HSV_PURPLE)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights,
    layer_colemak_lights,
    layer_switcher_lights,  // Overrides other layers
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,
	layer_numpad_lights
	
	
);


layer_state_t default_layer_state_set_user(layer_state_t state) {

	rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));// && layer_state_cmp(default_layer_state,_QWERTY));
	rgblight_set_layer_state(1, layer_state_cmp(state, _COLEMAK));// && layer_state_cmp(default_layer_state,_COLEMAK));


    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	//rgblight_set_layer_state(0, layer_state_cmp(default_layer_state, _QWERTY));// && layer_state_cmp(default_layer_state,_QWERTY));
	//rgblight_set_layer_state(6, layer_state_cmp(default_layer_state, _COLEMAK));// && layer_state_cmp(default_layer_state,_COLEMAK));

    rgblight_set_layer_state(2, layer_state_cmp(state, _SOFTWARE));
	rgblight_set_layer_state(3, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(4, layer_state_cmp(state, _RAISE));
	rgblight_set_layer_state(5, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(6, layer_state_cmp(state, _NUMPAD));
	
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("Dane\nEvans"), false);

    oled_write_ln_P(PSTR(""), false);

	//snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)


    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        case _COLEMAKDH:
            oled_write_ln_P(PSTR("CmkDH"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QWERTY:
        case _COLEMAKDH:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        case _SOFTWARE:
            oled_write_P(PSTR("Swit\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    switch (keycode) {
        case KC_RUS:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_QWERTY);
                default_layer_set(1UL<<_COLEMAK);
                //layer_on(_COLEMAK);
                tap_code16(C(S(KC_9)));
                layout = RUS;
            }
            return false;
        case KC_LAT:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_COLEMAK);
                default_layer_set(1UL<<_QWERTY);
                //layer_on(_QWERTY);
                tap_code16(C(S(KC_8)));
                layout = LAT;
            }
            return false;
        case KC_SHORT:
            if (record->event.pressed) {
                default_layer_set(1UL<<_QWERTY);
            } else {
                default_layer_set(1UL<<_COLEMAK);
            }
            
            return false;

        case KC_COLEMAKDH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAKDH);
            }
            return false;
        case KC_LOWER:
            {
            static bool isShifted;
            
            if (record->event.pressed) {
                layer_on(_LOWER);
                //update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                isShifted = get_mods() & LAYER_LOCK_KEY;
                if(!isShifted){
                    del_mods(LAYER_LOCK_KEY);
                    layer_off(_LOWER);
                }
                //update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            }
        case KC_RAISE:
            {
            static bool isShifted;
            isShifted = get_mods() & LAYER_LOCK_KEY;
            if (record->event.pressed) {
                layer_on(_RAISE);
                //update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                if(!isShifted){
                    del_mods(LAYER_LOCK_KEY);
                    layer_off(_RAISE);
                }
                //update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            }
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_DESK:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_COLEMAK);
                //default_layer_set(1UL<<_QWERTY);
                //layer_on(_QWERTY);
                tap_code16(A(G(KC_H)));
            }
            return false;
        case LT(0,KC_M):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RBRC); // Intercept hold function to send Ctrl-X
                //tap_code16(G(KC_SPC)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode    
        case LT(0,KC_SLSH):
            if (!record->tap.count && record->event.pressed) {
                //tap_code16(KC_BSLS); // Intercept hold function to send Ctrl-X
                 //tap_code16(S(KC_SLSH)); // Intercept hold function to send Ctrl-X
                if (IS_MAC){
                    default_layer_set(1UL<<_QWERTY);
                    tap_code16(C(S(KC_8)));
                    layout = LAT;
                    SEND_STRING("mymac\n");
                } 
                else SEND_STRING("Carramba77_\n");
                //tap_code16(G(KC_SPC)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_TAB):
            if (!record->tap.count && record->event.pressed) {
                //tap_code16(KC_BSLS); // Intercept hold function to send Ctrl-X
                 tap_code16(S(KC_TAB)); // Intercept hold function to send Ctrl-X
                //tap_code16(G(KC_SPC)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_SPC):
            if (!record->tap.count && record->event.pressed) {
                //tap_code16(KC_BSLS); // Intercept hold function to send Ctrl-X
                 tap_code16(G(KC_SPC)); // Intercept hold function to send Ctrl-X
                //tap_code16(G(KC_SPC)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode        
        case LT(0,KC_GRV):
            if (!record->tap.count && record->event.pressed) {
                caps_word_set(true);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode  
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
            return true;
        case KC_LANG:
            if (record->event.pressed) {
                if (IS_MAC) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_SPC);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LSFT);
                }
            } else {
                if (IS_MAC) {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_SPC);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LSFT);
                }
            }
            //break;
            return false;
        case ALT_TAB:
                if (IS_MAC) {
                    if (record->event.pressed) {
                        //SEND_STRING(SS_DOWN(X_LALT));
                        SEND_STRING(SS_DOWN(X_LGUI));
                        SEND_STRING(SS_TAP(X_TAB));
                    } else {
                        //SEND_STRING(SS_UP(X_LALT));
                        SEND_STRING(SS_UP(X_LGUI));
                    }
                } else {
                    if (record->event.pressed) {
                        SEND_STRING(SS_DOWN(X_LALT));
                        //SEND_STRING(SS_DOWN(X_LGUI));
                        SEND_STRING(SS_TAP(X_TAB));
                    } else {
                        SEND_STRING(SS_UP(X_LALT));
                        //SEND_STRING(SS_UP(X_LGUI));
                    }
                }
            
            break;
        case U_DOLLAR:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_6) ));
            }
            break;
        case U_P_VAL:
            if (record->event.pressed) {
                //SEND_STRING(    SS_LCTL(SS_LALT(SS_TAP(X_V)))   SS_TAP(X_K) SS_TAP(X_ENT));
                tap_code16(C(A(KC_V)));tap_code(KC_DOWN);tap_code(KC_DOWN);tap_code(KC_ENT);
            }
            break;
         case U_P_FMT:
            if (record->event.pressed) {
                tap_code16(C(A(KC_V)));tap_code(KC_DOWN);tap_code(KC_DOWN);tap_code(KC_DOWN);tap_code(KC_ENT);
                            }
            break;
         case U_P_FRM:
            if (record->event.pressed) {
                SEND_STRING(    SS_LCTL(SS_LALT(SS_TAP(X_V)))    SS_TAP(X_A) SS_TAP(X_ENT));
            }
            break;
        case U_SCLN:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_5) SS_TAP(X_KP_9) ));
            }
            break;
        case U_LESS:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_0) SS_TAP(X_KP_6 ) SS_TAP(X_KP_0)));
            }
            break;
        case U_MORE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_0) SS_TAP(X_KP_6 ) SS_TAP(X_KP_2)));
            }
            break;
        case U_CLR:
            if (record->event.pressed) {
                if (layout == RUS)
                {
                   if (get_mods() & MOD_MASK_CTRL)
                   {
                    del_mods(MOD_MASK_CTRL);
                    SEND_STRING(SS_TAP(X_LALT) SS_TAP(X_S) SS_TAP(X_QUOT) SS_TAP(X_2) SS_TAP(X_TAB) SS_TAP(X_0) SS_TAP(X_TAB));
                   }
                   else{
                    SEND_STRING(SS_TAP(X_LALT) SS_TAP(X_Z) SS_TAP(X_N) SS_TAP(X_X) SS_TAP(X_T));
                   }
                }
                else if (layout == LAT)
                {
                   if (get_mods() & MOD_MASK_CTRL)
                   {
                    del_mods(MOD_MASK_CTRL);
                    SEND_STRING(SS_TAP(X_LALT) SS_TAP(X_S) SS_TAP(X_QUOT) SS_TAP(X_2) SS_TAP(X_TAB) SS_TAP(X_0) SS_TAP(X_TAB));
                   }
                   else{
                   tap_code(KC_LALT); tap_code(KC_Z); tap_code(KC_N); tap_code(KC_X);tap_code(KC_T);
                   }
                }
            }
            break;
        case U_QUOT:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_4) ));
            }
            break;
        case KC_DSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_UP);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_UP);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_DEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_DOWN);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_DOWN);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_WSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_A);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_A);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_WEND:
            if (record->event.pressed) {
                if (IS_MAC) {
                    /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_K);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (IS_MAC) {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_K);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_WM_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_WM_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_WM_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_WM_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
            break;
    }
    return true;
}
__attribute__((weak)) bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
    case KC_SCLN:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_MINS:
    case KC_UNDS:
    case KC_RAISE:
    
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        switch (get_highest_layer(layer_state)) {
    			case _COLEMAK:
				case _QWERTY:
				case _COLEMAKDH:
					if (clockwise) {
						//tap_code16(C(S(KC_TAB)));
                         tap_code(KC_LEFT);
                        
					} else {
					    //tap_code16(C(KC_TAB));
                         tap_code(KC_RIGHT);
                        
					}
				break;
			case _RAISE:
			case _LOWER:
					if (clockwise) {
						tap_code(KC_UP);
					} else {
						tap_code(KC_DOWN);
					}                    
				break;
			default:
					if (clockwise) {
						tap_code(KC_UP);
					} else {
						tap_code(KC_DOWN);
					}
				break;
		}
		
        } else if (index == 0) {
			switch (get_highest_layer(layer_state)) {
    			case _COLEMAK:
				case _QWERTY:
				case _COLEMAKDH:
					if (clockwise) {
						//tap_code(KC_WH_U);
                        //tap_code(KC_WH_U);
                        //tap_code(KC_WH_U);
                       tap_code(KC_PGUP);
					} else {
						//tap_code(KC_WH_D);
                        //tap_code(KC_WH_D);
                        //tap_code(KC_WH_D);
                        tap_code(KC_PGDN);
					}
				break;
			case _RAISE:
			case _LOWER:
					if (clockwise) {
						tap_code(KC_VOLD);
					} else {
						tap_code(KC_VOLU);
					}                    
				break;
			default:
					if (clockwise) {
						tap_code(KC_UP);
					} else {
						tap_code(KC_DOWN);
					}
				break;
		}
    }
    return true;
}

#endif
#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_init_user() {
      uint8_t rcv;

      // set TrackPoint sensitivity
      PS2_MOUSE_SEND(0xE2, "tpsens: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpsens: 0x81");
      PS2_MOUSE_SEND(0x4A, "tpsens: 0x4A");
      PS2_MOUSE_SEND(0xFF, "tpsens: 0xFF");

      // set TrackPoint Negative Inertia factor
      PS2_MOUSE_SEND(0xE2, "tpnegin: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpnegin: 0x81");
      PS2_MOUSE_SEND(0x4D, "tpnegin: 0x4D");
      PS2_MOUSE_SEND(0x06, "tpnegin: 0x06");

      // set TrackPoint speed
      // (transfer function upper plateau speed)
      PS2_MOUSE_SEND(0xE2, "tpsp: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpsp: 0x81");
      PS2_MOUSE_SEND(0x60, "tpsp: 0x60");
      PS2_MOUSE_SEND(0xB4, "tpsp: 0xB4");

      // inquire pts status
      rcv = ps2_host_send(0xE2);
      rcv = ps2_host_send(0x2C);
      rcv = ps2_host_recv_response();
      if ((rcv & 1) == 1) {
        // if on, disable pts
        rcv = ps2_host_send(0xE2);
        rcv = ps2_host_send(0x47);
        rcv = ps2_host_send(0x2C);
        rcv = ps2_host_send(0x01);
      }
  }
  #endif
  