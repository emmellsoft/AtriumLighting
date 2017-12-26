#include "ChristmasEffect.h"
#include "Support.h"
#include "Constants.h"

// The normal, static color of the LEDs
#define DEFAULT_R	50
#define DEFAULT_G	0
#define DEFAULT_B	0

// The brighest twinkle color
#define TWINKLE_R	255
#define TWINKLE_G	70
#define TWINKLE_B	30

// The timing of a twinkle
#define FADE_UP_DURATION	200
#define FADE_DOWN_DURATION	800

// States of a twinkle
#define TWINKLER_FADING_MODE_INIT		0
#define TWINKLER_FADING_MODE_DELAY		1
#define TWINKLER_FADING_MODE_FADE_UP	2
#define TWINKLER_FADING_MODE_FADE_DOWN	3

// Minimum distance between two twinkling LEDs
#define MIN_TWINKLING_LED_DISTANCE	4

void Twinkler::Reset()
{
	_fadingMode = TWINKLER_FADING_MODE_INIT;
}

bool Twinkler::Update()
{
	if (!_colorFader.Update() || (_fadingMode == TWINKLER_FADING_MODE_INIT))
	{
		switch (_fadingMode)
		{
		case TWINKLER_FADING_MODE_INIT:
		{
			uint16_t duration = random(1000, 2000);
			_colorFader.Init(DEFAULT_R, DEFAULT_G, DEFAULT_B, DEFAULT_R, DEFAULT_G, DEFAULT_B, duration);
			_fadingMode = TWINKLER_FADING_MODE_DELAY;
			break;
		}

		case TWINKLER_FADING_MODE_DELAY:
			_colorFader.Init(DEFAULT_R, DEFAULT_G, DEFAULT_B, TWINKLE_R, TWINKLE_G, TWINKLE_B, FADE_UP_DURATION);
			_fadingMode = TWINKLER_FADING_MODE_FADE_UP;
			break;

		case TWINKLER_FADING_MODE_FADE_UP:
			_colorFader.Init(TWINKLE_R, TWINKLE_G, TWINKLE_B, DEFAULT_R, DEFAULT_G, DEFAULT_B, FADE_DOWN_DURATION);
			_fadingMode = TWINKLER_FADING_MODE_FADE_DOWN;
			break;

		case TWINKLER_FADING_MODE_FADE_DOWN:
			return false;
		}
	}

	return true;
}

uint32_t Twinkler::GetColor()
{
	return _colorFader.GetColor();
}

ChristmasEffect::ChristmasEffect(int totalLedCount)
{
	_totalLedCount = totalLedCount;

	for (size_t i = 0; i < TWINKLER_COUNT; i++)
	{
		_virtualLedIndices[i] = 255;
		_twinklers[i].Reset();
	}

	for (size_t i = 0; i < TWINKLER_COUNT; i++)
	{
		_virtualLedIndices[i] = ChooseVirtualLedIndex();
	}
}

void ChristmasEffect::Update()
{
	for (size_t i = 0; i < TWINKLER_COUNT; i++)
	{
		if (!_twinklers[i].Update())
		{
			_twinklers[i].Reset();
			_virtualLedIndices[i] = 255;
			_virtualLedIndices[i] = ChooseVirtualLedIndex();
		}
	}
}

uint8_t ChristmasEffect::ChooseVirtualLedIndex()
{
	while (true)
	{
		// Just pick a random LED
		uint8_t virtualLedIndex = random(_totalLedCount);

		// Ensure that the selected LED is far enough from all existing twinklings
		bool hit = false;
		for (size_t i = 0; i < TWINKLER_COUNT; i++)
		{
			int distance = virtualLedIndex - _virtualLedIndices[i];
			if (distance < 0)
			{
				distance = -distance;
			}

			if (distance <= MIN_TWINKLING_LED_DISTANCE)
			{
				hit = true;
				break;
			}
		}

		if (!hit)
		{
			return virtualLedIndex;
		}
	}
}

uint32_t ChristmasEffect::GetColor(int virtualLedIndex)
{
	// Is this LED currently twinkling?
	for (size_t i = 0; i < TWINKLER_COUNT; i++)
	{
		if (_virtualLedIndices[i] == virtualLedIndex)
		{
			// Yes -- get the twinkle color
			return _twinklers[i].GetColor();
		}
	}

	return Support::ComposeColor(DEFAULT_R, DEFAULT_G, DEFAULT_B);
}
