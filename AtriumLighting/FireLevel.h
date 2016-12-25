#ifndef _FIRELEVEL_h
#define _FIRELEVEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// This class is creating a flickering effect to be assigned to one individual LED.
// Call Update() once in each loop and get the current "flickering value"
// between 0.0 and 1.0 by calling the GetNormalizedValue() method.
class FireLevel
{
public:
	FireLevel();

	void Update();

	float GetNormalizedValue();

private:
	uint16_t _value;
	int16_t _direction;
	uint8_t _stepsLeft;

	void Reset();
};


#endif

