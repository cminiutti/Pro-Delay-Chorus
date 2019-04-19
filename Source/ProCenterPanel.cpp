/*
  ==============================================================================

    ProCenterPanel.cpp
    Created: 4 Apr 2019 3:15:06pm
    Author:  minut

  ==============================================================================
*/

#include "ProCenterPanel.h"

ProCenterPanel::ProCenterPanel(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);

	mMenuBar = new ProCenterPanelMenuBar(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(mMenuBar);

	mEffectsPanel = new ProEffectsPanel(inProcessor);
	mEffectsPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
	addAndMakeVisible(mEffectsPanel);

	mMenuBar->addFxTypeComboBoxListener(mEffectsPanel);
}

ProCenterPanel::~ProCenterPanel()
{
	mMenuBar->removeFxTypeComboBoxListener(mEffectsPanel);
}