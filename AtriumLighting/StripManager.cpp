#include "StripManager.h"
#include "Effect.h"

void StripManager::ApplyEffect(Effect *effect)
{
	for (size_t virtualLedIndex = 0; virtualLedIndex < GetTotalLedCount(); virtualLedIndex++)
	{
		uint32_t color = effect->GetColor(virtualLedIndex);

		SetPixelColor(virtualLedIndex, color);
	}

	Show();
}
