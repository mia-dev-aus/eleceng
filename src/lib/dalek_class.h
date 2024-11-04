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
	int irData[numIrSensors][dataLength];
	int filter_data[fbForder + ffForder][numIrSensors][dataLength / 2];

	public:
	// Contains the intensity of the signal detected from each ir sensor.
	// int ir_sensors[num_ir_sensors][data_length]{};
	int irSensors[numIrSensors]{};

	// Contains the time record of each microphone
	struct {
		uint32_t left;
		uint32_t mid;
		uint32_t right;
	} microphones;

    void turnLeft();
    void turnRight();
    void stop();

	// Sets up the Digital pins for LED output.
	void ledSetup();
	// Sets up Digital pins for reading microphones
	void micSetup();
	// Gets the sensor data from IR sensors.
	uint32_t updateIrData();
	// IR filters. 
	void Dalek::motorSetup();
	void Dalek::exterminateSetup();
	uint32_t Dalek::driveMotor();

	void Dalek::applySubFilter();
	void Dalek::applyIirFilter();
	// Updates led output depending on direction.
	uint32_t updateLeds();
	// updates the time record of each microphone.
	uint32_t updateSoundData();
};

#endif
