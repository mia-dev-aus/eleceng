#include "dalek_class.h"
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

void Dalek::update_sensor_data() {
    ir_sensors[0] = analogRead(IR_SENSOR_4);
    ir_sensors[1] = analogRead(IR_SENSOR_3);
    ir_sensors[2] = analogRead(IR_SENSOR_2);
    ir_sensors[3] = analogRead(IR_SENSOR_1);
    ir_sensors[4] = analogRead(IR_SENSOR0);
    ir_sensors[5] = analogRead(IR_SENSOR1);
    ir_sensors[6] = analogRead(IR_SENSOR2);
    ir_sensors[7] = analogRead(IR_SENSOR3);
    ir_sensors[8] = analogRead(IR_SENSOR4);
}

void Dalek::update_leds() {
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
}