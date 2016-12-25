#ifndef _FLAMEDETECTOR_h
#define _FLAMEDETECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Note: This class is not yet used in this project...

// A class that helps detecting a real live flame.
// The constructor takes the pin where the flame sensor is connected,
// a threshold of the sensor (where a sensor reading above this level
// means a flame is detected) and a certaintyCount which is the number
// of consecutive Update()-times a flame needs to be detected (or no longer detected)
// for the state to change. (I.e. using a value of 1 means that if one
// single call to Update() detects a flame the state is changed, and a number
// of 10 means that at least 10 Update()-calls in a row must have the same reading
// for the state to change.)
//
// Usage:
// Call Update() frequently. It returns TRUE if the state has changed.
// Call the IsFlameDetected() to get the current state.
class FlameDetector
{
public:
	FlameDetector(uint8_t pin, int threshold, int certaintyCount);

	bool Update();
	bool IsFlameDetected();

private:
	uint8_t _pin;
	int _threshold;
	int _certaintyCount;
	bool _flameDetected;
	int _certaintyCountDown;
};

#endif

