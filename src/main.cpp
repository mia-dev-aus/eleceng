#include <Arduino.h>
#include "lib/array.h"
#include "lib/tests.h"
#include "lib/dalek_class.h"

Dalek dalek{};

void setup() {
    // put your setup code here, to run once:
	dalek.led_setup();
}

void loop() {
    // put your main code here, to run repeatedly:
	dalek.update_sensor_data();

	// Index of sensor facing the pluger direction.
	int mid_sensor{get_mid_index(num_ir_sensors)};
	// Sensor detecting max intensity.
	int max_sensor{get_max_index(dalek.ir_sensors, num_ir_sensors)};

	if (max_sensor < mid_sensor) {
		dalek.turn_left();
	} else if (max_sensor > mid_sensor) {
		dalek.turn_right();
	} else {
		dalek.stop();
	}

	dalek.update_leds();
}

// put function definitions here:

