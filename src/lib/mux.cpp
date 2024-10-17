#include "constants.h"
#include "mux.h"
#include <Arduino.h>

void mux_setup() {
    pinMode(mux_pin0, OUTPUT);
    pinMode(mux_pin1, OUTPUT);
    pinMode(mux_pin2, OUTPUT);
    pinMode(mux_pin3, OUTPUT);
}

int read_mux_analog_pin(int pin) {
    reset_mux_pins();
    delay(time_delay_ms);

    // Convert pin integer to binary output
    if  (pin % 2 == 1) {
        digitalWrite(mux_pin0, HIGH);
    }
    pin /= 2;
    if  (pin % 2 == 1) {
        digitalWrite(mux_pin1, HIGH);
    }
    pin /= 2;
    if  (pin % 2 == 1) {
        digitalWrite(mux_pin2, HIGH);
    }
    pin /= 2;
    if  (pin % 2 == 1) {
        digitalWrite(mux_pin3, HIGH);
    }
    
    delay(time_delay_ms);
    return analogRead(MUX_SIGNAL_PIN);
};

void reset_mux_pins() {
    digitalWrite(mux_pin0, LOW);
    digitalWrite(mux_pin1, LOW);
    digitalWrite(mux_pin2, LOW);
    digitalWrite(mux_pin3, LOW);
}
