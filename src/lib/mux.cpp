#include "constants.h"
#include "mux.h"
#include <Arduino.h>

void muxSetup() {
    for (int i = 0; i < numIrSensors; ++i) {
        pinMode(muxPin0 + i, OUTPUT);
    }
}

// Reads the nth analog pin, where n is pin.
// The analog pins are labelled from left to right, 0 - 8.
int readMuxAnalogPin(int pin) {
    resetMuxPins();
    digitalWrite(muxPin0 + pin, HIGH);

    return analogRead(A0);
};

// Switches off mux pins.
void resetMuxPins() {
    for (int i = 0; i < numIrSensors; ++i) {
        digitalWrite(muxPin0 + i, LOW);
    }
}
