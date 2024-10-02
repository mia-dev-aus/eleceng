#include "mux.h"
#include <Arduino.h>

constexpr int signal_pin{A0};
constexpr int mux_pin0{8};
constexpr int mux_pin1{9};
constexpr int mux_pin2{10};
constexpr int mux_pin3{11};

int read_mux_analog_pin(int pin) {
    reset_mux_pins();

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
    
    return analogRead(signal_pin);
};

void reset_mux_pins() {
    digitalWrite(mux_pin0, LOW);
    digitalWrite(mux_pin1, LOW);
    digitalWrite(mux_pin2, LOW);
    digitalWrite(mux_pin3, LOW);
}
