#ifndef DALEK_CLASS_H
#define DALEK_CLASS_H

constexpr int num_ir_sensors{9};
// Might be unecessary
constexpr double sensor_circumfrence_cm{129.2};

class Dalek {
	public:
    // Contains the intensity of the signal detected from each ir sensor.
	int ir_sensors[num_ir_sensors]{};
	
	// Indicate if the dalek needs to turn left, right, or not turn to face the target.
	bool left{false};
	bool right{false};
	bool straight{false};

    void turn_left();
    void turn_right();
    void stop();
};

#endif
