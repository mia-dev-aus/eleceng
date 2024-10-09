#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int time_delay_ms{5};
constexpr int max_time_delay_ms{5000};

// LEDs
constexpr int left_led{2};
constexpr int mid_led{4};
constexpr int right_led{7};

constexpr int num_ir_sensors{9};

// Mux pins
constexpr int signal_pin{A0};
constexpr int mux_pin0{8};
constexpr int mux_pin1{9};
constexpr int mux_pin2{10};
constexpr int mux_pin3{11};

// Service times
constexpr int num_services{2};
constexpr int update_sensor_data_time{200};
constexpr int update_leds_time{200};

#endif
