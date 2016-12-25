#ifndef _TWOSTRIPMANAGER_h
#define _TWOSTRIPMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include <Adafruit_NeoPixel.h>
#include "StripManager.h"


// An implementation of the abstract StripManager class that
// concatenates two LED strips into one, and virtually rearrange
// the LEDs which comes in a different order in the two strips.
class TwoStripManager : public StripManager
{
public:
	void Init();
	void SetBrightness(uint8_t brightness);
	void SetPixelColor(uint16_t virtualLedIndex, uint32_t color);
	void Clear();
	void Show();

private:
	Adafruit_NeoPixel _strip1 = Adafruit_NeoPixel(LEDS_STRIP_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800);
	Adafruit_NeoPixel _strip2 = Adafruit_NeoPixel(LEDS_STRIP_2, PIN_STRIP_2, NEO_GRB + NEO_KHZ800);

	uint8_t GetStripNumber(int virtualLedIndex);
	uint8_t GetLedIndex(int virtualLedIndex);
};


#endif

