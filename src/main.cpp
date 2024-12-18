#include <Arduino.h>
#include "lib/array.h"
#include "lib/mux.h"
#include "lib/dalek_class.h"
#include "lib/constants.h"

Dalek dalek{};
void changeDir(uint32_t currTime);
void updateExterminate(uint32_t currTime);

void setup() {
	Serial.begin(9600);
	dalek.ledSetup();
	muxSetup();
	dalek.motorSetup();
	dalek.exterminateSetup();

	#ifdef MIC_FUNC_ON
	dalek.mic_setup();
	#endif
}

// records timestamp of last time the dalek was not moving left or right.
uint32_t lastTurn = 0;

void loop() {
	uint32_t serviceTimes[numServices] = {0};
	uint32_t currTime = millis();
	// Max time before next service executes.
	uint32_t nextTime = currTime + maxTimeDelayMs;

	// Executes Dalek instruction evert n milliseconds, where n is specified in
	// serviceTimes.
	// Look at service manager example in lectures slides for more detail.
	for (int service = 0; service < numServices; ++service) {
		if (serviceTimes[service] <= currTime) {
			// In order of service occuring
			switch (service) {
			case 0:
				// debugging
				for (int i = 0; i < numIrSensors; ++i) {
					Serial.print(dalek.irSensors[i]);
					Serial.print(' ');
				}
				Serial.print('\n');

				serviceTimes[service] += dalek.updateIrData();
				changeDir(currTime);

				break;
			case 1:
				serviceTimes[service] += dalek.updateLeds();
				break;
			case 2: 
				serviceTimes[service] += dalek.driveMotor();
				break;
			case 3: 
				updateExterminate(currTime);
				serviceTimes[service] += dalek.executeExterminate();
			} 

		}
		nextTime = (serviceTimes[service] < nextTime) ? serviceTimes[service] : nextTime;		
	}
	delay((nextTime > currTime) ? nextTime - currTime : 0);
}

// Helper function for main
// Changes the Daleks action depending on the Ir data in dalek.irSensors.
void changeDir(uint32_t currTime) {
	// Index of sensor facing the pluger direction.
	int midSensor{getMidIndex(numIrSensors)};
	// Sensor detecting max intensity.
	int maxSensor{getMaxIndex(dalek.irSensors, numIrSensors)};

	if (dalek.irSensors[maxSensor] < minSensorValue) {
		return;
	} 

	if (maxSensor < midSensor) {
		dalek.turnLeft();
		lastTurn = currTime;
	} else if (maxSensor > midSensor) {
		dalek.turnRight();
		lastTurn = currTime;
	} else {
		dalek.stop();
	}
}

// Stops extermination after the dalek starts turning again.
void updateExterminate(uint32_t currTime) {
	if (currTime - lastTurn > 1000) {
		dalek.exterminate();
	} else {
		dalek.stopExterminate();
	}
}

#ifdef MIC_FUNC_ON
double calc_pol_dir() {
	uint32_t time_diff1 = dalek.microphones.mid - dalek.microphones.mid;
	uint32_t time_diff2 = dalek.microphones.mid - dalek.microphones.right;
	uint32_t time_diff3 = dalek.microphones.left - dalek.microphones.right;

	double radius = mic_radius_mil * 1000;

	double x{(time_diff3 * sound_speed * 1.0) / (2 *sqrt(3.0) * radius)};
	double y{(time_diff2 * sound_speed * 1.0 - x*radius*sqrt(3.0) / (sound_speed * 1.0)) * (sound_speed*1.0/(-3*radius*1.0))};

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
#endif
