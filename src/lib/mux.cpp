#include "constants.h"
#include "mux.h"
#include <Arduino.h>

// The analog pins will be labelled from right to left, 0 - 8.

void muxSetup() {
    for (int i = 0; i < numIrSensors; ++i) {
        pinMode(muxPin0 + i, OUTPUT);
    }
}

int readMuxAnalogPin(int pin) {
    resetMuxPins();
    digitalWrite(muxPin0 + pin, HIGH);

    return analogRead(A0);
};

void resetMuxPins() {
    for (int i = 0; i < numIrSensors; ++i) {
        digitalWrite(muxPin0 + i, LOW);
    }
}
