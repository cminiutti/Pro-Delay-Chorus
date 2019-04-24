/*
  ==============================================================================

    ProTopPanel.h
    Created: 4 Apr 2019 3:15:54pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "ProPanelBase.h"

class ProTopPanel	:	public ProPanelBase, public Button::Listener, public ComboBox::Listener
{
public:

	ProTopPanel(ProPluginAudioProcessor* inProcessor);
	~ProTopPanel();

	void paint(Graphics& g) override;

	void buttonClicked(Button*) override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	void displaySaveAsPopup();
	void updatePresetComboBox();

	ScopedPointer<ComboBox> mPresetDisplay;
	ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
};