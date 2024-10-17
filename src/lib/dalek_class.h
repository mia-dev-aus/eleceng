#ifndef DALEK_CLASS_H
#define DALEK_CLASS_H

#include "constants.h"
#include <Arduino.h>

class Dalek {
	private:	
	// Indicate if the dalek needs to turn left, right, or not turn to face the target.
	bool left{false};
	bool right{false};
	// Might be unnecessary.
	bool straight{false};

	public:
	// Contains the intensity of the signal detected from each ir sensor.
	int ir_sensors[num_ir_sensors]{};

	// Contains the time record of each microphone
	struct {
		uint32_t left;
		uint32_t mid;
		uint32_t right;
	} microphones;

    void turn_left();
    void turn_right();
    void stop();

	// Sets up the Digital pins for LED output.
	void led_setup();
	// Sets up Digital pins for reading microphones
	void mic_setup();
	// Gets the sensor data from IR sensors.
	uint32_t update_ir_data();
	// Updates led output depending on direction.
	uint32_t update_leds();
	// updates the time record of each microphone.
	uint32_t update_sound_data();
};

#endif
