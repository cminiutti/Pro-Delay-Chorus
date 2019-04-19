/*
  ==============================================================================

    ProComboBox.cpp
    Created: 8 Apr 2019 9:16:57pm
    Author:  minut

  ==============================================================================
*/

#include "ProComboBox.h"

ProComboBox::ProComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID)
	: juce::ComboBox(parameterID)
{
	mAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);
}

ProComboBox::~ProComboBox()
{

}