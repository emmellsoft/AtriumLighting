#ifndef _COLORFADER_h
#define _COLORFADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// This is a small help class that lets a color fade from one to another during a given time span.
//
// Usage:
// The constructor takes the "from color" (as individual RGB-component bytes) and the "to color" plus the duration in milliseconds.
// Call the Update() method which will return TRUE as long as the destination color hasn't yet been reached.
// The GetColor() method returns the current color.
class ColorFader
{
public:
	void Init(uint8_t fromR, uint8_t fromG, uint8_t fromB, uint8_t toR, uint8_t toG, uint8_t toB, uint16_t durationMs);

	// Returns FALSE when completed.
	bool Update();

	uint32_t GetColor();

private:
	unsigned long _startMs;
	uint16_t _durationMs;
	uint8_t _fromR;
	uint8_t _fromG;
	uint8_t _fromB;
	uint8_t _toR;
	uint8_t _toG;
	uint8_t _toB;
};

#endif

