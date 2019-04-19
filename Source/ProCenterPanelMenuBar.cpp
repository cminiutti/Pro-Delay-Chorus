/*
  ==============================================================================

    ProCenterPanelMenuBar.cpp
    Created: 4 Apr 2019 3:15:19pm
    Author:  minut

  ==============================================================================
*/

#include "ProCenterPanelMenuBar.h"
#include "ProParameters.h"

ProCenterPanelMenuBar::ProCenterPanelMenuBar(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

	const int width = 85;

	mFxTypeComboBox = new ProComboBox(mProcessor->parameters, ProParameterID[pParameter_DelayType]);
	mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
	mFxTypeComboBox->addItem("DELAY", 1);
	mFxTypeComboBox->addItem("CHORUS", 2);
	mFxTypeComboBox->setSelectedItemIndex(static_cast<int>(*mProcessor->parameters.getRawParameterValue("Type")));
	addAndMakeVisible(mFxTypeComboBox);
}

ProCenterPanelMenuBar::~ProCenterPanelMenuBar()
{

}

void ProCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mFxTypeComboBox->addListener(inListener);
}

void ProCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mFxTypeComboBox->removeListener(inListener);
}