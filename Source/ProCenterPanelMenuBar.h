/*
  ==============================================================================

    ProCenterPanelMenuBar.h
    Created: 4 Apr 2019 3:15:19pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"
#include "ProComboBox.h"

class ProCenterPanelMenuBar : public ProPanelBase
{
public:

	ProCenterPanelMenuBar(ProPluginAudioProcessor* inProcessor);
	~ProCenterPanelMenuBar();

	void addFxTypeComboBoxListener(ComboBox::Listener *inListener);
	void removeFxTypeComboBoxListener(ComboBox::Listener *inListener);

private:

	ScopedPointer<ProComboBox> mFxTypeComboBox;
};