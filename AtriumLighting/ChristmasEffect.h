#ifndef _CHRISTMASEFFECT_h
#define _CHRISTMASEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "ColorFader.h"

// A small helper class that produces a twinkle color effect.
class Twinkler
{
public:
	void Reset();
	bool Update();
	uint32_t GetColor();

private:
	ColorFader _colorFader;
	uint8_t _fadingMode;
};


// The total number of simultaneous twinkle effects.
#define TWINKLER_COUNT	6


// An effect for the christmas holiday.
// All LEDs are soft red with a random twinkle effect.
class ChristmasEffect : public Effect
{
public:
	ChristmasEffect();

	void Update();

	uint32_t GetColor(int virtualLedIndex);

private:
	uint8_t _virtualLedIndices[TWINKLER_COUNT];
	Twinkler _twinklers[TWINKLER_COUNT];

	uint8_t ChooseVirtualLedIndex();
};


#endif

