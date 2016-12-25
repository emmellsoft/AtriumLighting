#ifndef _EFFECT_h
#define _EFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// The abstract Effect class.
// This is the base class for all LED strip effects.
// It has an Update() method that should be called in each loop and a GetColor() that gives the color of an individual LED.
class Effect
{
public:
	virtual void Update() { };

	virtual uint32_t GetColor(int virtualLedIndex) = 0;
};


#endif

