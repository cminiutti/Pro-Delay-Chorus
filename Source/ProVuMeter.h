/*
  ==============================================================================

    ProVuMeter.h
    Created: 24 Apr 2019 12:28:33pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class ProVuMeter : public Component, public Timer
{
public:

	ProVuMeter(ProPluginAudioProcessor* inProcessor);
	~ProVuMeter();

	void paint(Graphics& g) override;

	void timerCallback() override;

	void setParameterID(int inParameterID);

private:

	int mParameterID;

	float mCh0Level;
	float mCh1Level;

	ProPluginAudioProcessor* mProcessor;
};