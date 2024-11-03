#include "constants.h"
#include "mux.h"
#include <Arduino.h>

// The analog pins will be labelled from right to left, 0 - 8.

void mux_setup() {
    for (int i = 0; i < num_ir_sensors; ++i) {
        pinMode(mux_pin0 + i, OUTPUT);
    }
}

int read_mux_analog_pin(int pin) {
    reset_mux_pins();
    digitalWrite(mux_pin0 + pin, HIGH);

    if (pin >= 0 && pin <= 2) {
        return analogRead(MUX_SIGNAL_PIN1);
    } else if (pin >= 3 && pin <= 5) {
        return analogRead(MUX_SIGNAL_PIN2);

    } else if (pin >= 6 && pin <= 8) {
        return analogRead(MUX_SIGNAL_PIN3);

    }

};

void reset_mux_pins() {
    for (int i = 0; i < num_ir_sensors; ++i) {
        digitalWrite(mux_pin0 + i, LOW);
    }
}
