#include "dalek_class.h"

void Dalek::turn_left() {
    left = true;
    right = false;
    straight = false;
}

void Dalek::turn_right() {
    left = false;
    right = true;
    straight = false;
}

void Dalek::stop() {
    left = false;
    right = false;
    straight = true;
}
