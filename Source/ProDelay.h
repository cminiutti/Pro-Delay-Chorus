/*
  ==============================================================================

    ProDelay.h
    Created: 3 Apr 2019 11:09:29am
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProAudioHelpers.h"

enum ProDelayType
{
	pProDelayType_Delay = 0,
	pProDelayType_Chorus = 1,
};

class ProDelay
{
public:

	ProDelay();
	~ProDelay();

	void setSampleRate(double inSampleRate);

	void reset();

	void process(float* inAudio, float inTime, float inFeedback, float inWetDry, float inType, float* inModBuffer, float* outAudio, int inNumSamplesToRender);

private:

	double getInterpolatedSample(float inDelayTimeInSamples);

	double mSampleRate;
	double mBuffer[maxDelayBufferSize];
	double mFeedbackSample;

	float mTimeSmoothed;

	int mDelayIndex;
};
