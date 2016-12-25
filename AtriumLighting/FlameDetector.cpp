#include "FlameDetector.h"

FlameDetector::FlameDetector(uint8_t pin, int threshold, int certaintyCount)
{
	_pin = pin;
	_threshold = threshold;
	_certaintyCount = certaintyCount;
	_certaintyCountDown = -1;
}

bool FlameDetector::Update()
{
	int currentValue = analogRead(_pin);
	bool flameDetected = currentValue < _threshold;

	if (_certaintyCountDown == -1)
	{
		_flameDetected = flameDetected;
		_certaintyCountDown = 0;
		return true;
	}
	else if (_flameDetected == flameDetected)
	{
		_certaintyCountDown = _certaintyCount;
		return false;
	}
	else if (_certaintyCountDown > 0)
	{
		_certaintyCountDown--;
		return false;
	}
	else
	{
		_flameDetected = flameDetected;
		return true;
	}
}

bool FlameDetector::IsFlameDetected()
{
	return _flameDetected;
}