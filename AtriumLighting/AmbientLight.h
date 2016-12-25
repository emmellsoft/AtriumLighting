#ifndef _AMBIENTLIGHT_h
#define _AMBIENTLIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


enum AmbientLightState
{
	Unknown,
	Dark,
	Twilight,
	Light
};


// This class is a generic ambient light measurer which can be used for any purpose.
// In its constuctor it takes the pin number to a photo resistor and the low and high level of the twilight.
// Below the low level of twilight is DARK, above the high level of twilight is LIGHT -- and in between is TWILIGHT.
// 
// Usage:
// Call Update() "now and then" (doesn't need to be too often; roughly once a second is more than enough)
// After having updated, you can ask the GetState() to get the current light state.
// The GetTwilightFactor() will return a float between (including) 0.0 and 1.0
// where 0.0 is DARK and 1.0 is LIGHT and a number in between is the twilight zone.
//
// The mechanism is deliberately reacting slowly in order to reduce false light changes
// (like exposed to an artificial light during night time).
class AmbientLight
{
public:
	AmbientLight(uint8_t photoResistorPin, int lowTwilight, int highTwilight);

	void Update();

	AmbientLightState GetState();
	float GetTwilightFactor();

private:
	uint8_t _photoResistorPin;
	uint8_t _uncertaintyCountdown;
	int _lowTwilight;
	int _highTwilight;
	unsigned long _lastTime;
	float _averageLight;
	AmbientLightState _currentState;
	float _twilightFactor;
	bool _isStable;
	AmbientLightState _switchingToState;
	unsigned long _switchingStateStartTime;

	float CalculateNewAverage(int currentMeasurement, float currentAverage);
	AmbientLightState GetMomentaryState();
	void SetCurrentStableState(AmbientLightState state);
	float CalculateTwilightFactor();
};


#endif

