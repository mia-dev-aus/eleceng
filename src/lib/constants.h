#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int time_delay_ms{5};
constexpr int max_time_delay_ms{5000};

// LEDs
constexpr int left_led{3};
constexpr int mid_led{2};
constexpr int right_led{1};

// Sensors
constexpr int num_ir_sensors{9};
constexpr int num_mic{3};

// Mux pins. From 0 - 8. E.G. mux_pin4 = mix_pin0 + 4
#define MUX_SIGNAL_PIN1 A0
#define MUX_SIGNAL_PIN2 A1
#define MUX_SIGNAL_PIN3 A2
constexpr int mux_pin0{2};

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

// Filter
// #define FILTER_ORDER 4
// #define SCALE_FACTOR
// constexpr int data_length = 9600;
// constexpr int64_t a[FILTER_ORDER] = {};

#endif
