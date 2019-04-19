/*
  ==============================================================================

    ProGain.h
    Created: 3 Apr 2019 11:09:23am
    Author:  minut

  ==============================================================================
*/

#pragma once

class ProGain
{
public:

	ProGain();
	~ProGain();

	void process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender);

private:
};
