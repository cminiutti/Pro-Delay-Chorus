/*
  ==============================================================================

    ProLFO.h
    Created: 3 Apr 2019 11:09:17am
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProAudioHelpers.h"

class ProLFO
{
public:

	ProLFO();

	~ProLFO();

	void reset();

	void setSampleRate(double inSampleRate);

	void process(float inRate, float inDepth, float inNumSamples);

	float* getBuffer();

private:

	double mSampleRate;

	float mPhase;
	
	float mBuffer[maxDelayBufferSize];
};