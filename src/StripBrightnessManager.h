#ifndef _STRIPBRIGHTNESSMANAGER_h
#define _STRIPBRIGHTNESSMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class StripManager;
class AmbientLight;

// This class helps to control the brightness of the stip using the AmbientLight helper.
//
// Usage:
// Call Init() once and then Update() in each loop.
// Update() will return TRUE if the strip is turned ON at all, and FALSE if it is turned OFF.
class StripBrightnessManager
{
public:
	StripBrightnessManager(StripManager *stripManager, AmbientLight *ambientLight);

	void Init();
	bool Update();

private:
	StripManager *_stripManager;
	AmbientLight *_ambientLight;
	uint8_t _currentBrightness;
};

#endif

