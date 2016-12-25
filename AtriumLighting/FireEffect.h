#ifndef _FIREEFFECT_h
#define _FIREEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "FireLevel.h"
#include "Effect.h"

#define FIRE_LEVEL_COUNT 30




// A candle light effect.
// This class uses an array of FireLevel objects that represent one individual LED pixel.
// Note that the number of FireLevels may be less than the total number of LEDs.
// If so the same FireLevel objects is reused again (which should not be noticable
// unless the FIRE_LEVEL_COUNT is too low).
class FireEffect : public Effect
{
public:
	void Update();

	uint32_t GetColor(int virtualLedIndex);

private:
	FireLevel _fireLevels[FIRE_LEVEL_COUNT];

	uint8_t ScaleValue(float value, uint8_t min, uint8_t max);
};



#endif