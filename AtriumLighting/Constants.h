#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//=====================================================
// Pins
//-----------------------------------------------------

// The pin of the first strip
#define PIN_STRIP_1			6

// The pin of the second strip
#define PIN_STRIP_2			5

// The photo resistor pin
#define PIN_PHOTO_RESISTOR	A0



//=====================================================
// LED information
//-----------------------------------------------------

// The number of LED modules (of 4 LEDs each) on strip 1
#define STRIP_1_MODULE_COUNT	5

// The number of LED modules (of 4 LEDs each) on strip 2
#define STRIP_2_MODULE_COUNT	6

// This is the maximum allowed brightness
#define LEDS_MAX_BRIGHTNESS		128



//=====================================================
// Ambient light
//-----------------------------------------------------

// The threshold between dark and twilight (below = dark, above = twilight)
#define TWILIGHT_LOW			630

// The threshold between light and twilight (below = twilight, above = light)
#define TWILIGHT_HIGH			800




//=====================================================
// Calculated constants
//
// Math magic explained: "<< 2" is the same thing as "times 4", but quicker and easier for the Arduino.
//-----------------------------------------------------

// The total number of LED modules
#define MODULE_COUNT			STRIP_1_MODULE_COUNT + STRIP_2_MODULE_COUNT

// The number of individual LEDs on strip 1
#define LEDS_STRIP_1			STRIP_1_MODULE_COUNT << 2

// The number of individual LEDs on strip 2
#define LEDS_STRIP_2			STRIP_2_MODULE_COUNT << 2

// The total number of individual LEDs
#define TOTAL_LED_COUNT			(STRIP_1_MODULE_COUNT + STRIP_2_MODULE_COUNT) << 2



#endif

