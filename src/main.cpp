#include <Arduino.h>
#include "lib/array.h"
#include "lib/tests.h"
#include "lib/dalek_class.h"

Dalek dalek{};

constexpr int left_led{2};
constexpr int mid_led{4};
constexpr int right_led{7};

void setup() {
    // put your setup code here, to run once:
	pinMode(left_led, OUTPUT);
	pinMode(mid_led, OUTPUT);
	pinMode(right_led, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
	int ir_sensors[9] = {1, 2, 9, 1, 1, 1, 9, 0, 0};
	int mid_sensor{get_mid_index(num_ir_sensors)};
	int max_sensor = get_max_index(ir_sensors, num_ir_sensors);

	if (max_sensor < mid_sensor) {
		dalek.turn_left();
	} else if (max_sensor > mid_sensor) {
		dalek.turn_right();
	} else {
		dalek.stop();
	}

	if (dalek.left) {
		digitalWrite(left_led, HIGH);
		digitalWrite(right_led, LOW);
		digitalWrite(mid_led, LOW);
	} else if (dalek.right) {
		digitalWrite(left_led, LOW);
		digitalWrite(right_led, HIGH);
		digitalWrite(mid_led, LOW);
	} else {
		digitalWrite(left_led, LOW);
		digitalWrite(right_led, LOW);
		digitalWrite(mid_led, HIGH);
	}
}

// put function definitions here:

