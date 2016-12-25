#ifndef _SUPPORT_h
#define _SUPPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


// Support class with generic functionality.
class Support
{
public:
	static uint32_t ComposeColor(uint8_t r, uint8_t g, uint8_t b);
};

#endif

