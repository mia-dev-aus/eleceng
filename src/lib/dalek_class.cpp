#include "constants.h"
#include "dalek_class.h"
#include "mux.h"
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

void Dalek::motorSetup() {
    pinMode(clockwisePin, OUTPUT);
    pinMode(counterclockwisePin, OUTPUT);
    pinMode(speedPin, OUTPUT);
}

void Dalek::exterminateSetup() {
    pinMode(exterminatePin, OUTPUT);
}

uint32_t Dalek::driveMotor() {
  int analogValue = analogRead(voltagePin);
  float voltage = analogValue * (5.0 / 1023.0); 

  int exterValue = analogRead(exterPin);
  float exterVolt = exterValue * (5.0 / 1023.0);

  if (exterVolt >= 3) {
    speed = 0;
    analogWrite(speedPin, speed);  
    digitalWrite(clockwisePin, LOW);
    digitalWrite(counterclockwisePin, LOW);
    digitalWrite(exterminatePin, HIGH);
    Serial.println("Exterminate!");
  } 

  else if (voltage > 1.1) {  
    speed = map(voltage * 100, 110, 200, 0, 255);
    analogWrite(speedPin, speed);
    digitalWrite(clockwisePin, HIGH);
    digitalWrite(counterclockwisePin, LOW);
    digitalWrite(exterminatePin, LOW);
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V, Motor Speed: ");
    Serial.println(speed);
  } 
  else if (voltage <= 0.9) {  
    speed = map(voltage * 100, 0, 90, 255, 0);
    analogWrite(speedPin, speed);
    digitalWrite(clockwisePin, LOW);
    digitalWrite(counterclockwisePin, HIGH);
    digitalWrite(exterminatePin, LOW);
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V, Motor Speed: ");
    Serial.println(speed);
  } 
  else {
    speed = 0;
    analogWrite(speedPin, speed);
    digitalWrite(clockwisePin, LOW);
    digitalWrite(counterclockwisePin, LOW);
    digitalWrite(exterminatePin, LOW);
    Serial.println("Motor Stopped: Voltage below range.");
  }

  return driveMotorTime;
}

void Dalek::setupButterworth() {
    butter<filterOrder>()
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
