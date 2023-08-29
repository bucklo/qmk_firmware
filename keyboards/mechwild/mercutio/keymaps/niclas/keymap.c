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
#include "raw_hid.h"

// Additional include for OLED support
#ifdef OLED_ENABLE
  #include "oled_driver.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
                                                                                                                  KC_MUTE,
      KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      MO(1),            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
      KC_LSFT, KC_SLSH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,           KC_RSFT,
      KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  KC_SPC,           KC_SPC,           KC_RALT, MO(2),            KC_RCTL ),

  [1] = LAYOUT_all(
                                                                                                                  KC_TRNS,
  	  KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  	  KC_TRNS,          KC_TRNS, KC_GRV,  KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_TRNS, KC_QUOT,
  	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_SLSH,          KC_UP,
  	  KC_TRNS, KC_TRNS, KC_TRNS,          KC_HOME, KC_TRNS,          KC_END,           KC_LEFT, KC_DOWN,          KC_RIGHT ),

  [2] = LAYOUT_all(
                                                                                                                  KC_TRNS,
  	  KC_TRNS,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
  	  KC_CAPS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
  	  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS ),

  [3] = LAYOUT_all(
                                                                                                                  KC_TRNS,
  	  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  	  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
  	  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

#ifdef ENCODER_ENABLE       // Encoder Functionality
    uint8_t selected_layer = 0;
    bool encoder_update_user(uint8_t index, bool clockwise) {
        #ifdef OLED_ENABLE
            oled_clear();
            oled_render();
        #endif
        switch (index) {
            case 0:         // This is the only encoder right now, keeping for consistency
                if ( clockwise ) {
                    if ( selected_layer  < 3 && keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
                        selected_layer ++;
                        layer_move(selected_layer);
                    } else {
                        tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
                    }
                } else if ( !clockwise ) {
                    if ( selected_layer  > 0 && keyboard_report->mods & MOD_BIT(KC_LSFT) ){
                        selected_layer --;
                        layer_move(selected_layer);
                    } else {
                        tap_code(KC_VOLD);
                    }
                }
        }
    return false;
    }
#endif

#ifdef OLED_ENABLE   // OLED Functionality
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180;       // flips the display 180 degrees if offhand
    }

    bool clear_screen = false;          // used to manage singular screen clears to prevent display glitch
    // static void render_name(void) {     // Render Mercutio Script Text
    //   oled_write_P(PSTR("Niclas"), false);
    // }

    // static void render_weather(void) {     // Render Mercutio Script Text
    //     oled_set_cursor(8,1);
    //     oled_write_P(PSTR("desc: moln"), false);
    //     oled_set_cursor(8,2);
    //     oled_write_P(PSTR("high: 10.0"), false);
    //     oled_set_cursor(8,3);
    //     oled_write_P(PSTR("low:  5.0"), false);
    //     oled_set_cursor(8,4);
    //     oled_write_P(PSTR("rain: 0.0"), false);
    // }


    void raw_hid_receive(uint8_t *data, uint8_t length) {
        // Parse the data here and update OLED
        if (data[0] == 0x01) {  // Custom command identifier
            oled_clear();
            oled_render();
            oled_write("Received: ", false);
            oled_write((char*)(data + 1), false);
        }
    }

    bool oled_task_user(void) {
        led_t led_state = host_keyboard_led_state();
        if ( !led_state.num_lock && !led_state.caps_lock && selected_layer == 0 && get_highest_layer(layer_state) == 0 ) {
            // render_name();
            // render_weather();
            clear_screen = true;
            // oled_set_cursor(8,1);
            
        } else {
            if (clear_screen == true) {
                oled_clear();
                oled_render();
                clear_screen = false;
            }
            // render_logo();
            oled_set_cursor(8,2);
            switch(selected_layer){
                case 0:
                    oled_write_P(PSTR("Simon"), false);
                    break;
                case 1:
                    oled_write_P(PSTR("was"), false);
                    break;
                case 2:
                    oled_write_P(PSTR("here"), false);
                    break;
                case 3:
                    oled_write_P(PSTR("lol"), false);
                    break;
                default:
                    oled_write_P(PSTR("Lock Layer ?"), false);    // Should never display, here as a catchall
            }
            oled_set_cursor(8,3);
            if (get_highest_layer(layer_state) == selected_layer) {
                oled_write_P(PSTR("            "), false);
            } else {
                switch (get_highest_layer(layer_state)) {
                    case 0:
                        oled_write_P(PSTR("all"), false);
                        break;
                    case 1:
                        oled_write_P(PSTR("your"), false);
                        break;
                    case 2:
                        oled_write_P(PSTR("base"), false);
                        break;
                    case 3:
                        oled_write_P(PSTR("are"), false);
                        break;
                    default:
                        oled_write_P(PSTR("Temp Layer ?"), false);    // Should never display, here as a catchall
                }
            }
            led_t led_state = host_keyboard_led_state();
            oled_set_cursor(8,0);
            oled_write_P(led_state.scroll_lock ? PSTR("SCRLK") : PSTR("     "), false);
            oled_set_cursor(8,1);
            oled_write_P(led_state.num_lock ? PSTR("NLCK ") : PSTR("     "), false);
            oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
        }
    return false;
    }
#endif
