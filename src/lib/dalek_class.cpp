#include "constants.h"
#include "dalek_class.h"
#include "mux.h"
#include "array.h"
#include <Arduino.h>
#include <Filters.h>
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <Filters/Butterworth.hpp>

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

void Dalek::exterminate() {
    exterminating = true;
}

void Dalek::stopExterminate() {
    exterminating = false;
}

bool Dalek::isNotTurning() {
    if (right == false && left == false) {
        return true;
    } else {
        return false;
    }
}

void Dalek::ledSetup() {
    pinMode(leftLed, OUTPUT);
	pinMode(midLed, OUTPUT);
	pinMode(rightLed, OUTPUT);
}

uint32_t Dalek::updateIrData() {
    for (int i{0}; i < numIrSensors; ++i) {
        for (int j{0}; j < dataLength; ++j) {
            irData[j] = readMuxAnalogPin(i);
        }

        applySubFilter();

        irSensors[i] = getAverage(filterData, dataLength / 2);

        // applyMovingAverage();
    }

    return updateIrDataTime;
}

void Dalek::motorSetup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
}

void Dalek::exterminateSetup() {
    pinMode(alarm, OUTPUT);
}

float Dalek::getRotSpeed() {
    return speedCo * SensorDisplacement[getMaxIndex(irSensors, numIrSensors)];
}

uint32_t Dalek::driveMotor() {
  float motorValue = getRotSpeed() * (5.0 / 1023.0);
  Serial.println(motorValue);

    // turn off exterminate alarm 
    if (right == true) {
    
      int speed = map(motorValue * 100, 100, 200, 0, 255);

      analogWrite(enA, speed); 
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);

      Serial.println("clockwise");

    } else if (left == true) {
      
      int speed = map(motorValue * 100, 0, 100, 255, 0);
      
      analogWrite(enA, speed); 
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      Serial.println("anti");

    } else if (left == false && right == false) {
      Serial.println("motor stop");

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);  

    }

    return driveMotorTime;
}

uint32_t Dalek::executeExterminate() {
    if (exterminating) {
        digitalWrite(alarm, HIGH);

        Serial.println("exterminate");

        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    } else {
        digitalWrite(alarm, LOW);
    }

    return executeExterminateTime;
}

// void Dalek::setupButterworth() {
//     butter<filterOrder>()
// }

void Dalek::applySubFilter() {
    for (int i = 0; i < dataLength / 2; ++i) {
        filterData[i] = irData[2 * i + 1] - irData[2* i];
    }
}

// void Dalek::applyIirFilter() {

        
// }

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

#ifdef MIC_FUNC_ON
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


void Dalek::micSetup() {
    pinMode(micMidPin, INPUT);
	pinMode(micLeftPin, INPUT);
	pinMode(micRightPin, INPUT);
}
#endif