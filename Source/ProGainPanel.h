/*
  ==============================================================================

    ProGainPanel.h
    Created: 4 Apr 2019 3:15:36pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"
#include "ProParameterKnob.h"

class ProGainPanel : public ProPanelBase
{
public:

	ProGainPanel(ProPluginAudioProcessor* inProcessor);
	~ProGainPanel();

	void paint(Graphics& g) override;

	void setParameterID(int inParameterID);

private:

	ScopedPointer<ProParameterKnob> mKnob;

};
