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
        // for (int j{0}; j < data_length; ++j) {
            ir_sensors[i] = read_mux_analog_pin(i);
        // }
    }
    return update_ir_data_time;
}

// Brielle's code
// void Dalek::applyIIRFilter(int32_t *data, int length, int64_t *a, int64_t *b, int64_t *outputArray) {
//  int order = FILTER_ORDER;
//  int64_t x[FILTER_ORDER + 1] = {0};
//  int64_t y[FILTER_ORDER + 1] = {0};
//  for (int n = 0; n < length; n++) {
//  for (int i = order; i > 0; i--) {
//  x[i] = x[i - 1];
//  }
//  x[0] = (int64_t)data[n] * SCALE_FACTOR;
//  int64_t filteredValue = 0;
//  for (int i = 0; i <= order; i++) {
//  filteredValue += b[i] * x[i];
//  }
//  for (int i = 1; i <= order; i++) {
//  filteredValue -= a[i] * y[i - 1];
//  }
//  for (int i = order - 1; i > 0; i--) {
//  y[i] = y[i - 1];
//  }
//  y[0] = filteredValue / SCALE_FACTOR;
//  outputArray[n] = filteredValue / SCALE_FACTOR;
//  }
// }

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
