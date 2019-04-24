/*
  ==============================================================================

    ProParameterKnob.cpp
    Created: 8 Apr 2019 9:16:48pm
    Author:  minut

  ==============================================================================
*/

#include "ProParameterKnob.h"

ProParameterKnob::ProParameterKnob(AudioProcessorValueTreeState& stateToControl, const String& parameterID, const String& parameterLabel)
	:	juce::Slider(parameterLabel)
{
	setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
	setRange(0.0f, 1.0f, 0.001f);

	mAttachment = new AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);
}

ProParameterKnob::~ProParameterKnob()
{

}