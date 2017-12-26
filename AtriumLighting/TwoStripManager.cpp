#include "TwoStripManager.h"

// The arrangement of LEDs within a module, both the actual layout of the two strips, and the requested "virtual" module:
// STRIP 1       STRIP 2      VIRTUAL MODULE
// (3)(0)        (0)(3)          (0)(1)
// (2)(1)        (1)(2)          (2)(3)
//
// Where (0) is the first LED of the module and (3) is the last.

// The layout of LED arrangement of the two strips, and how the virtual LEDs are arranged (as one consecutive strip)
//
//                            |--------------STRIP 1-----------------|---------------------STRIP 2------------------|
// Actual Module placement:    S1[4] - S1[3] - S1[2] - S1[1] - S1[0] - S2[0] - S2[1] - S2[2] - S2[3] - S2[4] - S2[5]
// Actual LED index:           16-19   12-15   8-11    4-7     0-3     0-3     4-7     8-11    12-15   16-19   20-23
// Virtual Module index:       0       1       2       3       4       5       6       7       8       9       10
// Virtual LED index:          0-3     4-7     8-11    12-15   16-19   20-23   24-27   28-31   32-35   36-39   40-43
//
// Since the Arduino is placed in between the two strips, strip 1 is going from the right to the left and strip 2 from the left to the right.
// The virtual strip is starting at the far left and going right.
// Having one long (virtual) homogenous strip makes it easier to create cool effects than having to deal with two with different layouts.

int TwoStripManager::GetTotalLedCount()
{
	return TOTAL_LED_COUNT;
}

void TwoStripManager::Init()
{
	_strip1.begin();
	_strip2.begin();

	SetBrightness(0);
}

void TwoStripManager::SetBrightness(uint8_t brightness)
{
	_strip1.setBrightness(brightness);
	_strip2.setBrightness(brightness);

	if (brightness == 0)
	{
		_strip1.clear();
		_strip2.clear();
		Show();
	}
}

void TwoStripManager::Show()
{
	_strip1.show();
	_strip2.show();
}

// Returns (strip) 1 or (strip) 2 giving the virtual LED index.
uint8_t TwoStripManager::GetStripNumber(int virtualLedIndex)
{
	if (virtualLedIndex < LEDS_STRIP_1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

// Returns the "physical" LED index on its strip given the virtual LED index.
uint8_t TwoStripManager::GetLedIndex(int virtualLedIndex)
{
	// Get the "module sub index" of the LED, i.e. which of the 4 LEDs the given LED is sitting on within its module (a value 0-3):
	uint8_t moduleSubIndex = virtualLedIndex % 4;

	if (virtualLedIndex < LEDS_STRIP_1)
	{
		// The LED is on strip 1.

		// Identify the 4-module of the physical LED and the index of the first LED of that module:
		uint8_t firstLedIndex = (STRIP_1_MODULE_COUNT - 1 - (virtualLedIndex >> 2)) << 2;

		// The physical order of the LEDs within a module should be converted to a virtual module:
		switch (moduleSubIndex)
		{
		case 0: return firstLedIndex + 3;
		case 1: return firstLedIndex;
		case 2: return firstLedIndex + 2;
		case 3: return firstLedIndex + 1;
		}
	}
	else
	{
		// The LED is on strip 2.

		// Make the virtual LED index start on 0:
		virtualLedIndex -= LEDS_STRIP_1;

		// Identify the 4-module of the physical LED and the index of the first LED of that module:
		uint8_t firstLedIndex = (virtualLedIndex >> 2) << 2;

		// The physical order of the LEDs within a module should be converted to a virtual module:
		switch (moduleSubIndex)
		{
		case 0: return firstLedIndex;
		case 1: return firstLedIndex + 3;
		case 2: return firstLedIndex + 1;
		case 3: return firstLedIndex + 2;
		}
	}

	return 0; // This line can't be reached, but the compiler can't see that...  ;-)
}

void TwoStripManager::SetPixelColor(uint16_t virtualLedIndex, uint32_t color)
{
	uint8_t stripNumber = GetStripNumber(virtualLedIndex);
	uint8_t ledIndex = GetLedIndex(virtualLedIndex);

	switch (stripNumber)
	{
	case 1:
		_strip1.setPixelColor(ledIndex, color);
		break;
	case 2:
		_strip2.setPixelColor(ledIndex, color);
		break;
	}
}

