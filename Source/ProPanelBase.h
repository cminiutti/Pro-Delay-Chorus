/*
  ==============================================================================

    ProPanelBase.h
    Created: 4 Apr 2019 3:14:51pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "ProInterfaceDefines.h"

class ProPanelBase	:	public Component
{
public:

	ProPanelBase(ProPluginAudioProcessor* inProcessor);
	~ProPanelBase();

	void paint(Graphics &g) override;

protected:

	ProPluginAudioProcessor* mProcessor;
};