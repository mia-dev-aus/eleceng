#include <Arduino.h>
#include "lib/array.h"
#include "lib/tests.h"
#include "lib/dalek_class.h"

Dalek dalek{};

void setup() {
    // put your setup code here, to run once:
	// Set up the pinmodes here
	int irsensor1{0};
	pinMode(irsensor1, INPUT);
	int ledout1{4};
	pinMode(ledout1, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
	
	int mid_sensor{get_mid_index(num_ir_sensors)};
	int max_sensor = get_max_index(dalek.ir_sensors, num_ir_sensors);

	if (max_sensor < mid_sensor) {
		dalek.turn_left();
	} else if (max_sensor > mid_sensor) {
		dalek.turn_right();
	} else {
		dalek.stop();
	}

	if (dalek.left) {
		
	}

}

// put function definitions here:

