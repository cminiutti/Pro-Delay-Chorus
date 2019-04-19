/*
  ==============================================================================

    ProParameterKnob.h
    Created: 8 Apr 2019 9:16:48pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProParameterKnob : public Slider
{
public:

	ProParameterKnob(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
	~ProParameterKnob();

private:

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
};
