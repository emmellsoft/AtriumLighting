#include "StripManager.h"
#include "Effect.h"


void StripManager::ApplyEffect(Effect *effect)
{
	for (size_t virtualLedIndex = 0; virtualLedIndex < TOTAL_LED_COUNT; virtualLedIndex++)
	{
		uint32_t color = effect->GetColor(virtualLedIndex);

		SetPixelColor(virtualLedIndex, color);
	}

	Show();
}
