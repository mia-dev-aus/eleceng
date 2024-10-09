#include <Arduino.h>
#include "lib/array.h"
#include "lib/tests.h"
#include "lib/dalek_class.h"
#include "lib/constants.h"

Dalek dalek{};
void change_dir();

void setup() {
    // put your setup code here, to run once:
	dalek.led_setup();
}

void loop() {
	int service_times[num_services] = {0};
	uint32_t curr_time = millis();
	// Max time before next service executes.
	uint32_t next_time = curr_time + max_time_delay_ms;

	// Look at service manager example in lectures slides for detail
	for (int s = 0; s < num_services; ++s) {
		if (service_times[s] <= curr_time) {
			// In order of service occuring
			if (s == 0) {
				service_times[s] += dalek.update_sensor_data();
				change_dir();
			} else if (s == 1) {
				service_times[s] += dalek.update_leds();
			}
		}
		next_time = (service_times[s] < next_time) ? service_times[s] : next_time;		
	}
	delay(next_time - curr_time);
}

// Helper function for main
void change_dir() {
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

}
