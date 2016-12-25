#include "FireLevel.h"


#define FIRE_MAX_LEVEL_VALUE 65535
#define FIRE_MIN_LEVEL_DIR 500
#define FIRE_MAX_LEVEL_DIR 5000
#define FIRE_MIN_LEVEL_STEPS 10
#define FIRE_MAX_LEVEL_STEPS 20

FireLevel::FireLevel()
{
	_value = random(0, 65536);
	Reset();
}

void FireLevel::Reset()
{
	_direction = random(FIRE_MIN_LEVEL_DIR, FIRE_MAX_LEVEL_DIR + 1);

	if ((_value > FIRE_MAX_LEVEL_VALUE * 0.9) || ((_value > FIRE_MAX_LEVEL_VALUE * 0.1) && (random(100) < 50)))
	{
		_direction = -_direction;
	}

	_stepsLeft = random(FIRE_MIN_LEVEL_STEPS, FIRE_MAX_LEVEL_STEPS + 1);
}

void FireLevel::Update()
{
	int32_t value = _value;

	value += _direction;

	if (value < 0)
	{
		value = 0;
		_stepsLeft = 0;
	}
	else if (value > FIRE_MAX_LEVEL_VALUE)
	{
		value = FIRE_MAX_LEVEL_VALUE;
		_stepsLeft = 0;
	}

	_value = value;

	if (_stepsLeft <= 0)
	{
		Reset();
	}
	else
	{
		_stepsLeft--;
	}
}

float FireLevel::GetNormalizedValue()
{
	return (float)_value / FIRE_MAX_LEVEL_VALUE;
}
