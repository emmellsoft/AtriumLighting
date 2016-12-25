#ifndef _STRIPMANAGER_h
#define _STRIPMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"

class Effect;

// Helper class that virtualizes a number of LED strips into one, consecutive LED strip.
class StripManager
{
public:
	virtual void Init() { };
	virtual void SetBrightness(uint8_t brightness) { };
	
	void ApplyEffect(Effect *effect);

protected:
	virtual void Show() { };
	virtual void SetPixelColor(uint16_t virtualLedIndex, uint32_t color) { };
};


#endif

