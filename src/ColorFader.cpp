#include "ColorFader.h"
#include "Support.h"


void ColorFader::Init(uint8_t fromR, uint8_t fromG, uint8_t fromB, uint8_t toR, uint8_t toG, uint8_t toB, uint16_t durationMs)
{
	_startMs = millis();
	_durationMs = durationMs;
	_fromR = fromR;
	_fromG = fromG;
	_fromB = fromB;
	_toR = toR;
	_toG = toG;
	_toB = toB;
}

bool ColorFader::Update()
{
	unsigned long duration = millis() - _startMs;
	return (duration <= _durationMs);
}

uint32_t ColorFader::GetColor()
{
	unsigned long duration = millis() - _startMs;
	if (duration >= _durationMs)
	{
		return Support::ComposeColor(_toR, _toG, _toB);
	}

	float completeFactor = (float)duration / (float)_durationMs;
	uint8_t r = (_toR - _fromR) * completeFactor + _fromR;
	uint8_t g = (_toG - _fromG) * completeFactor + _fromG;
	uint8_t b = (_toB - _fromB) * completeFactor + _fromB;

	return Support::ComposeColor(r, g, b);
}