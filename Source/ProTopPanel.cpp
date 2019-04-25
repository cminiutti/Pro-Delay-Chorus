/*
  ==============================================================================

    ProTopPanel.cpp
    Created: 4 Apr 2019 3:15:54pm
    Author:  minut

  ==============================================================================
*/

#include "ProTopPanel.h"

ProTopPanel::ProTopPanel(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);

	int button_x = 15;
	int button_y = 10;
	int button_w = 55;
	int button_h = 25;

	mNewPreset = new TextButton();
	mNewPreset->setButtonText("NEW");
	mNewPreset->setBounds(button_x, button_y, button_w, button_h);
	mNewPreset->addListener(this);
	addAndMakeVisible(mNewPreset);
	button_x = button_x + button_w;

	mSavePreset = new TextButton();
	mSavePreset->setButtonText("SAVE");
	mSavePreset->setBounds(button_x, button_y, button_w, button_h);
	mSavePreset->addListener(this);
	addAndMakeVisible(mSavePreset);
	button_x = button_x + button_w;

	mSaveAsPreset = new TextButton();
	mSaveAsPreset->setButtonText("SAVE AS");
	mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
	mSaveAsPreset->addListener(this);
	addAndMakeVisible(mSaveAsPreset);
	button_x = button_x + button_w;

	const int comboBox_w = 200;
	const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;

	mPresetDisplay = new ComboBox();
	mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
	mPresetDisplay->addListener(this);
	addAndMakeVisible(mPresetDisplay);

	updatePresetComboBox();
}

ProTopPanel::~ProTopPanel()
{

}

void ProTopPanel::paint(Graphics& g)
{
	ProPanelBase::paint(g);

	g.setColour(ProColour_1);
	g.setFont(font_2);

	const int label_w = 220;

	g.drawFittedText("Pro Audio Plugin", TOP_PANEL_WIDTH - label_w, 0, label_w, getHeight() - 10, Justification::centredRight, 1);
}

void ProTopPanel::buttonClicked(Button* b)
{
	ProPresetManager* presetManager = mProcessor->getPresetManager();

	if (b == mNewPreset)
	{
		presetManager->createNewPreset();
		updatePresetComboBox();
	}

	else if (b == mSavePreset)
	{
		presetManager->savePreset();
	}

	else if (b == mSaveAsPreset)
	{
		displaySaveAsPopup();
	}
}

void ProTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == mPresetDisplay)
	{
		ProPresetManager* presetManager = mProcessor->getPresetManager();

		const int index = mPresetDisplay->getSelectedItemIndex();
		presetManager->loadPreset(index);
	}
}

void ProTopPanel::displaySaveAsPopup()
{
	ProPresetManager* presetManager = mProcessor->getPresetManager();

	String currentPresetName = presetManager->getCurrentPresetName();

	AlertWindow window("SAVE AS", "Please nter a name for your Preset", AlertWindow::NoIcon);

	window.centreAroundComponent(this, getHeight(), getWidth());
	window.addTextEditor("presetName", currentPresetName, "preset name: ");
	window.addButton("Confirm", 1);
	window.addButton("Cancel", 0);

	if (window.runModalLoop())
	{
		String presetName = window.getTextEditor("presetName")->getText();
		presetManager->saveAsPreset(presetName);
	}

	updatePresetComboBox();
}

void ProTopPanel::updatePresetComboBox()
{
	ProPresetManager* presetManager = mProcessor->getPresetManager();
	String presetName = presetManager->getCurrentPresetName();

	mPresetDisplay->clear(dontSendNotification);

	const int numPresets = presetManager->getNumberOfPresets();

	for (int i = 0; i < numPresets; i++)
	{
		mPresetDisplay->addItem(presetManager->getPresetName(i), (i + 1));
	}

	mPresetDisplay->setText(presetManager->getCurrentPresetName());
}