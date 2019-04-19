/*
  ==============================================================================

    ProComboBox.h
    Created: 8 Apr 2019 9:16:57pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProComboBox : public ComboBox
{
public:

	ProComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
	~ProComboBox();

private:

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
};
