/*
  ==============================================================================

    ProAudioHelpers.h
    Created: 3 Apr 2019 11:08:49am
    Author:  minut

  ==============================================================================
*/

#pragma once

#define ProParameterSmoothingCoefficient_Generic 0.04
#define ProParameterSmoothingCoefficient_Fine 0.002

const static int maxDelayBufferSize = 48000;

// Linear interpolation function
inline float linear_interp(float x0, float x1, float fraction)
{
	return (1 - fraction) * x0 + fraction * x1;
}

// Soft clipping algorithm
inline double tanh_clip(double x)
{
	return x * (27 + x * x) / (27 + 9 * x * x);
}