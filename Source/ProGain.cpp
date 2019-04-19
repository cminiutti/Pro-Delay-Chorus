/*
  ==============================================================================

    ProGain.cpp
    Created: 3 Apr 2019 11:09:23am
    Author:  minut

  ==============================================================================
*/

#include "ProGain.h"
#include "JuceHeader.h"

ProGain::ProGain()
{

}

ProGain::~ProGain()
{

}

void ProGain::process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender)
{
	float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
	gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);

	for (int i = 0; i < inNumSamplesToRender; i++)
	{
		outAudio[i] = inAudio[i] * gainMapped;
	}
}
