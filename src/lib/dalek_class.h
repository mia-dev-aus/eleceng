#ifndef DALEK_CLASS_H
#define DALEK_CLASS_H

// Need to setup analog multiplexor
#define IR_SENSOR_4 A0
#define IR_SENSOR_3 A1
#define IR_SENSOR_2 A3
#define IR_SENSOR_1 A4
#define IR_SENSOR0 A5
#define IR_SENSOR1 A6
#define IR_SENSOR2 A7
// Not enough analog inputs for sensor 3 and 4.
#define IR_SENSOR3 A7
#define IR_SENSOR4 A7

// LEDs
constexpr int left_led{2};
constexpr int mid_led{4};
constexpr int right_led{7};

constexpr int num_ir_sensors{9};
// Might be unecessary
constexpr double sensor_circumfrence_cm{129.2};

class Dalek {
	private:	
	// Indicate if the dalek needs to turn left, right, or not turn to face the target.
	bool left{false};
	bool right{false};
	// Might be unnecessary.
	bool straight{false};

	public:
	// Contains the intensity of the signal detected from each ir sensor.
	int ir_sensors[num_ir_sensors]{};

    void turn_left();
    void turn_right();
    void stop();

	// Sets up the Digital pins for LED output.
	void led_setup();
	// Gets the sensor data from IR sensors.
	void update_sensor_data();
	// Updates led output depending on direction.
	void update_leds();

};

#endif
