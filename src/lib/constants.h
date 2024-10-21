#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int time_delay_ms{5};
constexpr int max_time_delay_ms{5000};

// LEDs
constexpr int left_led{2};
constexpr int mid_led{3};
constexpr int right_led{4};

// Sensors
constexpr int num_ir_sensors{9};
constexpr int num_mic{3};

// Mux pins
#define MUX_SIGNAL_PIN A0
constexpr int mux_pin0{8};
constexpr int mux_pin1{9};
constexpr int mux_pin2{10};
constexpr int mux_pin3{11};

// Service times
constexpr int num_services{2};
constexpr int update_ir_data_time{200};
constexpr int update_leds_time{200};
constexpr int update_sound_data_time{200};

// Microphone 
constexpr int mic_mid_pin{5};
constexpr int mic_left_pin{6};
constexpr int mic_right_pin{7};
constexpr int max_wait{1};
constexpr int mic_radius_mil{};

// Misc
constexpr int sound_speed{343};

#endif
