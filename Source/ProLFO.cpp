/*
  ==============================================================================

    ProLFO.cpp
    Created: 3 Apr 2019 11:09:17am
    Author:  minut

  ==============================================================================
*/

#include "ProLFO.h"
#include "JuceHeader.h"

ProLFO::ProLFO()
{

}

ProLFO::~ProLFO() 
{

}

void ProLFO::reset()
{
	mPhase = 0.0f;
	zeromem(mBuffer, sizeof(float) * maxDelayBufferSize);
}

void ProLFO::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void ProLFO::process(float inRate, float inDepth, float inNumSamples)
{
	const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);

	for (int i = 0; i < inNumSamples; i++)
	{
		mPhase = mPhase + (rate / mSampleRate);

		if (mPhase > 1.0f)
		{
			mPhase = mPhase - 1.0f;
		}

		const float lfoPosition = sinf(mPhase * double_Pi * 2) * inDepth;
		mBuffer[i] = lfoPosition;
	}
}

float* ProLFO::getBuffer()
{
	return mBuffer;
}


