/*
  ==============================================================================

    ProCenterPanel.h
    Created: 4 Apr 2019 3:15:06pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"
#include "ProCenterPanelMenuBar.h"
#include "ProEffectsPanel.h"

class ProCenterPanel : public ProPanelBase
{
public:

	ProCenterPanel(ProPluginAudioProcessor* inProcessor);
	~ProCenterPanel();

private:

	ScopedPointer<ProCenterPanelMenuBar> mMenuBar;
	ScopedPointer<ProEffectsPanel> mEffectsPanel;
};