#include "FireEffect.h"
#include "Support.h"

void FireEffect::Update()
{
	for (int i = 0; i < FIRE_LEVEL_COUNT; i++)
	{
		_fireLevels[i].Update();
	}
}

uint32_t FireEffect::GetColor(int virtualLedIndex)
{
	int levelIndex = (virtualLedIndex % FIRE_LEVEL_COUNT);

	float level1Value = _fireLevels[levelIndex].GetNormalizedValue();

	uint8_t r = ScaleValue(level1Value, 64, 128); // 64-128 is based on a max brightness of 128 (i.e. actual max = 32-64)
	uint8_t g = r * 0.55;
	uint8_t b = g * 0.2;

	return Support::ComposeColor(r, g, b);
}

uint8_t FireEffect::ScaleValue(float normalizedValue, uint8_t min, uint8_t max)
{
	int16_t scaled = normalizedValue * (max - min + 1) + min;
	if (scaled > 255)
	{
		return 255;
	}

	if (scaled < 0)
	{
		return 0;
	}

	return scaled;
}
