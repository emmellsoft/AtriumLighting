#include "AmbientLight.h"

#define MEASURE_INTERVAL_MILLIS			1000 // How often to check ambient light in milliseconds
#define UNCERTAINTY_COUNTDOWN_START		100 // The number of samples to take at startup
#define SWITCHING_STATE_DELAY_MILLIS	60000 // One minute

AmbientLight::AmbientLight(uint8_t photoResistorPin, int lowTwilight, int highTwilight)
{
	_photoResistorPin = photoResistorPin;
	_lowTwilight = lowTwilight;
	_highTwilight = highTwilight;
	_uncertaintyCountdown = UNCERTAINTY_COUNTDOWN_START;
	_lastTime = millis();
	_currentState = Unknown;
}

void AmbientLight::Update()
{
	unsigned long currentTime = millis();

	unsigned long duration;
	if (_uncertaintyCountdown > 0)
	{
		duration = 0;
	}
	else
	{
		duration = MEASURE_INTERVAL_MILLIS;
	}

	unsigned long millisPassed = currentTime - _lastTime;
	if (millisPassed < duration)
	{
		// Not yet time to measure
		return;
	}

	_lastTime = currentTime;

	int currentMeasurement = analogRead(_photoResistorPin);
	_averageLight = CalculateNewAverage(currentMeasurement, _averageLight);

	if (_uncertaintyCountdown > 0)
	{
		_uncertaintyCountdown--;
		if (_uncertaintyCountdown == 0)
		{
			// Now a trust-worthy average has been calculated.
			SetCurrentStableState(GetMomentaryState());
		}
	}
	else
	{
		AmbientLightState momentaryState = GetMomentaryState();
		if (momentaryState == _currentState)
		{
			// We are in a stable state.
			_isStable = true;

			if (_currentState == AmbientLightState::Twilight)
			{
				_twilightFactor = CalculateTwilightFactor();
			}
		}
		else if (_isStable || (_switchingToState != momentaryState))
		{
			// This is the first observed light state that differs from the current state.
			// It could just be a flickering -- just take a note that another state has been observed.

			_switchingToState = momentaryState;
			_switchingStateStartTime = currentTime;
			_isStable = false;
		}
		else
		{
			unsigned long switchingStateDuration = currentTime - _switchingStateStartTime;
			if (switchingStateDuration >= SWITCHING_STATE_DELAY_MILLIS)
			{
				SetCurrentStableState(momentaryState);
			}
		}
	}
}

float AmbientLight::CalculateNewAverage(int currentMeasurement, float currentAverage)
{
	if (_uncertaintyCountdown > 0)
	{
		if (_uncertaintyCountdown == UNCERTAINTY_COUNTDOWN_START)
		{
			return currentMeasurement;
		}

		return (0.7 * currentMeasurement) + (0.3 * currentAverage);
	}

	return (0.01 * currentMeasurement) + (0.99 * currentAverage);
}

AmbientLightState AmbientLight::GetMomentaryState()
{
	if (_averageLight <= _lowTwilight)
	{
		return AmbientLightState::Dark;
	}

	if (_averageLight >= _highTwilight)
	{
		return AmbientLightState::Light;
	}

	return AmbientLightState::Twilight;
}

void AmbientLight::SetCurrentStableState(AmbientLightState state)
{
	_currentState = state;
	_isStable = true;

	switch (state)
	{
	case Dark:
		_twilightFactor = 0;
		break;
	case Twilight:
		_twilightFactor = 1;
		break;
	case Light:
		_twilightFactor = CalculateTwilightFactor();
		break;
	default:
		break;
	}
}

float AmbientLight::CalculateTwilightFactor()
{
	float twilightLength = _highTwilight - _lowTwilight;
	
	float factor = (_averageLight - _lowTwilight) / twilightLength;

	if (factor < 0)
	{
		return 0;
	}

	if (factor > 1)
	{
		return 1;
	}

	return factor;
}

AmbientLightState AmbientLight::GetState()
{
	return _currentState;
}

float AmbientLight::GetTwilightFactor()
{
	return _twilightFactor;
}