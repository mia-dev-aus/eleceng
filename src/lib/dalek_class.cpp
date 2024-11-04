#include "constants.h"
#include "dalek_class.h"
#include "mux.h"
#include <Arduino.h>

void Dalek::turnLeft() {
    left = true;
    right = false;
    straight = false;
}

void Dalek::turnRight() {
    left = false;
    right = true;
    straight = false;
}

void Dalek::stop() {
    left = false;
    right = false;
    straight = true;
}

void Dalek::ledSetup() {
    pinMode(leftLed, OUTPUT);
	pinMode(midLed, OUTPUT);
	pinMode(rightLed, OUTPUT);
}

void Dalek::micSetup() {
    pinMode(micMidPin, INPUT);
	pinMode(micLeftPin, INPUT);
	pinMode(micRightPin, INPUT);
}

uint32_t Dalek::updateIrData() {
    for (int i{0}; i < numIrSensors; ++i) {
        for (int j{0}; j < dataLength; ++j) {
            irData[i][j] = readMuxAnalogPin(i);
        }
    }
    applySubFilter();
    applyIirFilter(); 
    
    for (int i = 0; i < numIrSensors; ++i) {
        irSensors[i] = getAverage(filterData, dataLength / 2);
    }

    return updateIrDataTime;
}

void Dalek::applySubFilter() {
    for (int i = 0; i < dataLength; ++i) {
        newData[i / dataLength] = data[i + 1] - data[i];
    }
}

void Dalek::applyIirFilter() {
    
        
}

uint32_t Dalek::getAverage(int32_t *data, int dataLength) {
    int64_t sum = 0;
    for (int i = 0; i < dataLength; ++i) {
        sum += data[i];
    }

    return sum / dataLength;
}

uint32_t Dalek::updateLeds() {
    if (left) {
		digitalWrite(leftLed, HIGH);
		digitalWrite(rightLed, LOW);
		digitalWrite(midLed, LOW);
	} else if (right) {
		digitalWrite(leftLed, LOW);
		digitalWrite(rightLed, HIGH);
		digitalWrite(midLed, LOW);
	} else {
		digitalWrite(leftLed, LOW);
		digitalWrite(rightLed, LOW);
		digitalWrite(midLed, HIGH);
	}

    return updateLedsTime;
}

uint32_t Dalek::updateSoundData() {
    microphones.left = 0;
    microphones.mid = 0;
    microphones.right = 0;
    uint32_t currTime = millis();

    while (millis() - currTime < maxWait) {
        microphones.left = (digitalRead(micMidPin) && !microphones.left) ? micros() : 0;
        microphones.mid = (digitalRead(micLeftPin) && !microphones.mid) ? micros() : 0;
        microphones.right = (digitalRead(micRightPin) && !microphones.right) ? micros() : 0;
    }

    return updateSoundDataTime;
}
