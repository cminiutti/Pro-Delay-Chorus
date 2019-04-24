/*
  ==============================================================================

    ProPresetManager.h
    Created: 19 Apr 2019 2:31:27pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".ppf"

class ProPresetManager
{
public:

	ProPresetManager(AudioProcessor* inProcessor);
	~ProPresetManager();

	void getXmlForPreset(XmlElement* inElement);
	void loadPresetForXml(XmlElement* inElement);

	int getNumberOfPresets();
	String getPresetName(int inPresetIndex);
	void createNewPreset();
	void savePreset();
	void saveAsPreset(String inPresetName);
	void loadPreset(int inPresetIndex);
	bool getIsCurrentPresetSaved();
	String getCurrentPresetName();

private:

	void storeLocalPresets();

	bool mCurrentPresetIsSaved;

	File mCurrentlyLoadedPreset;

	Array<File> mLocalPresets;

	String mCurrentPresetName;

	String mPresetDirectory;

	XmlElement* mCurrentPresetXml;

	AudioProcessor* mProcessor;
};