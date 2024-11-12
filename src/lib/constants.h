#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int timeDelayMs{5};
constexpr int maxTimeDelayMs{5000};

// LEDs
constexpr int leftLed{15};
constexpr int midLed{16};
constexpr int rightLed{17};

// Sensors
constexpr int numIrSensors{9};
constexpr int minSensorValue{20};
// Angular displacement of sensors (deg)
constexpr int SensorDisplacement[numIrSensors] = {115,80,45,10,0,10,45,90,115};

// Mux pins. From 0 - 8. E.G. mux_pin4 = mix_pin0 + 4
constexpr int muxPin0{2};

// Service times
constexpr int numServices{4};
constexpr int updateIrDataTime{200};
constexpr int updateLedsTime{200};
constexpr int updateSoundDataTime{200};
constexpr int driveMotorTime{200};
constexpr int executeExterminateTime{200};

// Microphone 
// Turn on/off mic functionality by commenting/uncommenting
// #define MIC_FUNC_ON

#ifdef MIC_FUNC_ON
constexpr int numMic{3};
constexpr int micMidPin{5};
constexpr int micLeftPin{6};
constexpr int micRightPin{7};
constexpr int maxWait{1};
constexpr int micRadiusMil{};

// Misc
constexpr int soundSpeed{343};

#endif

// Filter
constexpr int filterOrder{3};
constexpr int dataLength = 200;

// Motor and exterminate
constexpr int enA{11};
constexpr int in1{12};
constexpr int in2{13};
constexpr int alarm{18};

constexpr float speedCo{8.5};

#endif
