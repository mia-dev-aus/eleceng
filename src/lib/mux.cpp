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

    if (pin >= 0 && pin <= 2) {
        return analogRead(MUX_SIGNAL_PIN1);
    } else if (pin >= 3 && pin <= 5) {
        return analogRead(MUX_SIGNAL_PIN2);

    } else if (pin >= 6 && pin <= 8) {
        return analogRead(MUX_SIGNAL_PIN3);

    }

};

void resetMuxPins() {
    for (int i = 0; i < numIrSensors; ++i) {
        digitalWrite(muxPin0 + i, LOW);
    }
}
