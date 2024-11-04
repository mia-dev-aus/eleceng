#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int timeDelayMs{5};
constexpr int maxTimeDelayMs{5000};

// LEDs
constexpr int leftLed{13};
constexpr int midLed{12};
constexpr int rightLed{11};

// Sensors
constexpr int numIrSensors{9};
constexpr int numMic{3};
// Angular displacement of sensors
constexpr int SensorDisplacement[numIrSensors] = {};

// Mux pins. From 0 - 8. E.G. mux_pin4 = mix_pin0 + 4
#define MUX_SIGNAL_PIN1 A0
#define MUX_SIGNAL_PIN2 A1
#define MUX_SIGNAL_PIN3 A2
constexpr int muxPin0{2};

// Service times
constexpr int numServices{3};
constexpr int updateIrDataTime{200};
constexpr int updateLedsTime{200};
constexpr int updateSoundDataTime{200};
constexpr int driveMotorTime{200};

// Microphone 
constexpr int micMidPin{5};
constexpr int micLeftPin{6};
constexpr int micRightPin{7};
constexpr int maxWait{1};
constexpr int micRadiusMil{};

// Misc
constexpr int soundSpeed{343};

// Filter
constexpr int filterOrder{3};
constexpr int dataLength = 200;

// Motor and exterminate
constexpr int voltagePin = A0;
constexpr int exterPin = A1;
constexpr int clockwisePin = 9;
constexpr int counterclockwisePin = 10;
constexpr int speedPin = 11;  
constexpr int exterminatePin = 8;
int speed;


#endif
