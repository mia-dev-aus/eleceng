#include "constants.h"
#include "dalek_class.h"
#include "mux.h"
#include <Arduino.h>

void Dalek::turn_left() {
    left = true;
    right = false;
    straight = false;
}

void Dalek::turn_right() {
    left = false;
    right = true;
    straight = false;
}

void Dalek::stop() {
    left = false;
    right = false;
    straight = true;
}

void Dalek::led_setup() {
    pinMode(left_led, OUTPUT);
	pinMode(mid_led, OUTPUT);
	pinMode(right_led, OUTPUT);
}

void Dalek::mic_setup() {
    pinMode(mic_mid_pin, INPUT);
	pinMode(mic_left_pin, INPUT);
	pinMode(mic_right_pin, INPUT);
}

uint32_t Dalek::update_ir_data() {
    for (int i{0}; i < num_ir_sensors; ++i) {
        ir_sensors[i] = read_mux_analog_pin(i);
        delay(time_delay_ms);
    }
    return update_ir_data_time;
}

uint32_t Dalek::update_leds() {
    if (left) {
		digitalWrite(left_led, HIGH);
		digitalWrite(right_led, LOW);
		digitalWrite(mid_led, LOW);
	} else if (right) {
		digitalWrite(left_led, LOW);
		digitalWrite(right_led, HIGH);
		digitalWrite(mid_led, LOW);
	} else {
		digitalWrite(left_led, LOW);
		digitalWrite(right_led, LOW);
		digitalWrite(mid_led, HIGH);
	}

    return update_leds_time;
}

uint32_t Dalek::update_sound_data() {
    microphones.left = 0;
    microphones.mid = 0;
    microphones.right = 0;
    uint32_t curr_time = millis();

    while (millis() - curr_time < max_wait) {
        microphones.left = (digitalRead(mic_mid_pin) && !microphones.left) ? micros() : 0;
        microphones.mid = (digitalRead(mic_left_pin) && !microphones.mid) ? micros() : 0;
        microphones.right = (digitalRead(mic_right_pin) && !microphones.right) ? micros() : 0;
    }

    return update_sound_data_time;
}
