/*
  ==============================================================================

    ProEffectsPanel.h
    Created: 4 Apr 2019 3:15:30pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"
#include "ProParameterKnob.h"

enum ProEffectsPanelStyle
{
	pProEffectsPanelStyle_Delay,
	pProEffectsPanelStyle_Chorus,
	pProEffectsPanelStyle_TotalNumStyles
};

class ProEffectsPanel : public ProPanelBase, public ComboBox::Listener
{
public:

	ProEffectsPanel(ProPluginAudioProcessor* inProcessor);
	~ProEffectsPanel();

	void setEffectsPanelStyle(ProEffectsPanelStyle inStyle);

	void paint(Graphics& g) override;

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	ProEffectsPanelStyle mStyle;

	OwnedArray<ProParameterKnob> mKnobs;
};