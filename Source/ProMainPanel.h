/*
  ==============================================================================

    ProMainPanel.h
    Created: 4 Apr 2019 3:14:59pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"

#include "ProTopPanel.h"
#include "ProGainPanel.h"
#include "ProCenterPanel.h"

class ProMainPanel	:	public ProPanelBase
{
public:

	ProMainPanel(ProPluginAudioProcessor* inProcessor);
	~ProMainPanel();

private:

	ScopedPointer<ProTopPanel> mTopPanel;
	ScopedPointer<ProGainPanel> mInputGainPanel;
	ScopedPointer<ProGainPanel> mOutputGainPanel;
	ScopedPointer<ProCenterPanel> mCenterPanel;
};
