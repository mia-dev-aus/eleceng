#include <Arduino.h>
#include "lib/array.h"
#include "lib/tests.h"
#include "lib/mux.h"
#include "lib/dalek_class.h"
#include "lib/constants.h"

Dalek dalek{};
void change_dir();

void setup() {
	dalek.led_setup();
	dalek.mic_setup();
	mux_setup();
}

void loop() {
	uint32_t service_times[num_services] = {0};
	uint32_t curr_time = millis();
	// Max time before next service executes.
	uint32_t next_time = curr_time + max_time_delay_ms;

	// Look at service manager example in lectures slides for detail
	for (int service = 0; service < num_services; ++service) {
		if (service_times[service] <= curr_time) {
			// In order of service occuring
			switch (service) {
			case 0:
				service_times[service] += dalek.update_ir_data();
				change_dir();
				break;
			case 1:
				service_times[service] += dalek.update_leds();
				break;
			}
		}
		next_time = (service_times[service] < next_time) ? service_times[service] : next_time;		
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

double calc_pol_dir() {
	uint32_t time_diff1 = dalek.microphones.mid - dalek.microphones.mid;
	uint32_t time_diff2 = dalek.microphones.mid - dalek.microphones.right;
	uint32_t time_diff3 = dalek.microphones.left - dalek.microphones.right;
 
	double radius = mic_radius_mil * 1000;

	double x{(time_diff3 * sound_speed * pow(10, -6)) / (2 *sqrt(3.0) * radius)};
	double y{(time_diff2 * sound_speed * pow(10,  -6) - x*radius*sqrt(3.0) / (sound_speed * 1.0)) * (sound_speed*1.0/(-3*radius*1.0))};

	if (x > 0.0 && y > 0.0) {
		// First quad
		return atan(y/x);
	} else if (x < 0.0 && y > 0.0) {
		// Second quad
		return PI + atan(y/x);
	} else if (x < 0.0 && y < 0.0) {
		// Third quad
		return PI + atan(y/x);
	} else {
		// Fourth quad
		return atan(y/x);
	}
}

