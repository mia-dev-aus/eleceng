#ifndef DALEK_CLASS_H
#define DALEK_CLASS_H

#include "constants.h"
#include <Arduino.h>

class Dalek {
	private:	
	// Indicate if the dalek needs to turn left, right, or not turn to face the target.
	bool left{false};
	bool right{false};
	bool exterminating{false};
	// Might be unnecessary.
	bool straight{false};
	int irData[dataLength];
	int filterData[dataLength / 2];

	public:
	// Contains the intensity of the signal detected from each ir sensor.
	// int ir_sensors[num_ir_sensors][data_length]{};
	int irSensors[numIrSensors]{};

	#ifdef MIC_FUNC_ON
	// Contains the time record of each microphone
	struct {
		uint32_t left;
		uint32_t mid;
		uint32_t right;
	} microphones;

	void micSetup();
	// Gets the sensor data from IR sensors.

	// updates the time record of each microphone.
	uint32_t updateSoundData();
	#endif

    void turnLeft();
    void turnRight();
    void stop();
	void exterminate();
	void stopExterminate();

	bool isNotTurning();

	// Sets up the Digital pins for LED output.
	void ledSetup();
	// Sets up Digital pins for reading microphones
	
	uint32_t updateIrData();
	// IR filters. 
	void motorSetup();
	void exterminateSetup();
	float getRotSpeed();
	uint32_t driveMotor();
	uint32_t executeExterminate();

	void applySubFilter();
	// void Dalek::applyIirFilter();
	// Updates led output depending on direction.
	uint32_t updateLeds();
};

#endif
