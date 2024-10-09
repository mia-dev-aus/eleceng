#include "constants.h"
#include "mux.h"
#include <Arduino.h>


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
    return analogRead(signal_pin);
};

void reset_mux_pins() {
    digitalWrite(mux_pin0, LOW);
    digitalWrite(mux_pin1, LOW);
    digitalWrite(mux_pin2, LOW);
    digitalWrite(mux_pin3, LOW);
}
