/*
  ==============================================================================

    ProAudioHelpers.h
    Created: 3 Apr 2019 11:08:49am
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define ProParameterSmoothingCoefficient_Generic 0.04
#define ProParameterSmoothingCoefficient_Fine 0.002
#define ProMeterSmoothingCoefficient 0.2

const static int maxDelayBufferSize = 48000;

static inline float dBToNormalizedGain(float inValue)
{
	// Provide noise floor of 0.00001 for conversion
	float inValuedB = Decibels::gainToDecibels(inValue + 0.00001f);
	inValuedB = (inValuedB + 96.0f) / 96.0f;

	return inValuedB;
}

inline float linear_interp(float x0, float x1, float fraction)
{
	return (1 - fraction) * x0 + fraction * x1;
}

inline double tanh_clip(double x)
{
	return x * (27 + x * x) / (27 + 9 * x * x);
}

inline float pro_denormalize(float inValue)
{
	float absValue = fabs(inValue);

	if (absValue < 1e-15)
	{
		return 0.0f;
	}
	else
	{
		return inValue;
	}
}