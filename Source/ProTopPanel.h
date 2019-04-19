/*
  ==============================================================================

    ProTopPanel.h
    Created: 4 Apr 2019 3:15:54pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"

class ProTopPanel	:	public ProPanelBase
{
public:

	ProTopPanel(ProPluginAudioProcessor* inProcessor);
	~ProTopPanel();

	void paint(Graphics& g) override;

private:

};