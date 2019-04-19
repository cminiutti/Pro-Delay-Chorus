/*
  ==============================================================================

    ProDelay.cpp
    Created: 3 Apr 2019 11:09:29am
    Author:  minut

  ==============================================================================
*/

#include "ProDelay.h"
#include "JuceHeader.h"
#include "ProAudioHelpers.h"

ProDelay::ProDelay()
	: mSampleRate(-1), mFeedbackSample(0.0), mTimeSmoothed(0.0f), mDelayIndex(0)
{

}

ProDelay::~ProDelay() 
{

}

void ProDelay::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void ProDelay::reset()
{
	mTimeSmoothed = 0.0f;
	zeromem(mBuffer, (sizeof(double) * maxDelayBufferSize));
}

void ProDelay::process(float* inAudio, float inTime, float inFeedback, float inWetDry, float inType, float* inModBuffer, float* outAudio, int inNumSamplesToRender)
{
	const float wet = inWetDry;
	const float dry = 1.0f - wet;

	const float feedbackMapped = (inType == pProDelayType_Delay) ? jmap(inFeedback, 0.0f, 1.0f, 0.0f, 1.20f) : 0.0f;

	for (int i = 0; i < inNumSamplesToRender; i++)
	{
		if ((int)inType == pProDelayType_Delay)
		{
			mTimeSmoothed = mTimeSmoothed - ProParameterSmoothingCoefficient_Fine * (mTimeSmoothed - inTime);
		}
		else
		{
			const double delayTimeMod = (0.003 + (0.002 * inModBuffer[i]));
			mTimeSmoothed = mTimeSmoothed - ProParameterSmoothingCoefficient_Fine * (mTimeSmoothed - delayTimeMod);
		}

		const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);

		const double sample = getInterpolatedSample(delayTimeInSamples);

		// Apply soft clipping
		mBuffer[mDelayIndex] = tanh_clip(inAudio[i] + (mFeedbackSample * feedbackMapped));

		mFeedbackSample = sample;

		outAudio[i] = ((inAudio[i] * dry) + (sample * wet));

		mDelayIndex++;

		if (mDelayIndex >= maxDelayBufferSize)
		{
			mDelayIndex -= maxDelayBufferSize;
		}
	}
}

double ProDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
	double readPosition = (double)mDelayIndex - inDelayTimeInSamples;

	if (readPosition < 0.0f)
	{
		readPosition += maxDelayBufferSize;
	}

	int index_y0 = (int)readPosition - 1;

	if (index_y0 <= 0)
	{
		index_y0 += maxDelayBufferSize;
	}

	int index_y1 = readPosition;

	if (index_y1 > maxDelayBufferSize)
	{
		index_y1 -= maxDelayBufferSize;
	}

	const float sample_y0 = mBuffer[index_y0];
	const float sample_y1 = mBuffer[index_y1];
	const float fraction = readPosition - (int)readPosition;

	double outSample = linear_interp(sample_y0, sample_y1, fraction);

	return outSample;
}
