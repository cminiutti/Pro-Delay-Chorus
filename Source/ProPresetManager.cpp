/*
  ==============================================================================

    ProPresetManager.cpp
    Created: 19 Apr 2019 2:31:27pm
    Author:  minut

  ==============================================================================
*/

#include "ProPresetManager.h"

#if JUCE_WINDOWS
static const String directorySeperator = "\\";
#elif JUCE_MAC
static const String directorySeperator = "/";
#endif

ProPresetManager::ProPresetManager(AudioProcessor* inProcessor)
	:	mCurrentPresetIsSaved(false),
		mCurrentPresetName("Untitled"),
		mProcessor(inProcessor)
{
	const String pluginName = (String)mProcessor->getName();

	mPresetDirectory = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + directorySeperator + pluginName;

	if (!File(mPresetDirectory).exists())
	{
		File(mPresetDirectory).createDirectory();
	}

	storeLocalPresets();
}

ProPresetManager::~ProPresetManager()
{

}

void ProPresetManager::getXmlForPreset(XmlElement* inElement)
{
	auto& parameters = mProcessor->getParameters();

	for (int i = 0; i < parameters.size(); i++)
	{
		AudioProcessorParameterWithID* parameter =
		(AudioProcessorParameterWithID*)parameters.getUnchecked(i);

		inElement->setAttribute(parameter->paramID,
								parameter->getValue());
	}
}

void ProPresetManager::loadPresetForXml(XmlElement* inElement)
{
	mCurrentPresetXml = inElement;

	auto& parameters = mProcessor->getParameters();

	for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++)
	{
		const String paramID = mCurrentPresetXml->getAttributeName(i);
		const float value = mCurrentPresetXml->getDoubleAttribute(paramID);

		for (int j = 0; j < parameters.size(); j++)
		{
			AudioProcessorParameterWithID* parameter =
			(AudioProcessorParameterWithID*)parameters.getUnchecked(i);

			if (paramID == parameter->paramID)
			{
				parameter->setValueNotifyingHost(value);
			}
		}
	}
}

int ProPresetManager::getNumberOfPresets()
{
	return mLocalPresets.size();
}

String ProPresetManager::getPresetName(int inPresetIndex)
{
	return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void ProPresetManager::createNewPreset()
{
	auto& parameters = mProcessor->getParameters();

	for (int i = 0; i < parameters.size(); i++)
	{
		AudioProcessorParameterWithID* parameter =
		(AudioProcessorParameterWithID*)parameters.getUnchecked(i);

		const float defaultValue = parameter->getDefaultValue();

		parameter->setValueNotifyingHost(defaultValue);
	}

	mCurrentPresetIsSaved = false;
	mCurrentPresetName = "Untitled";
}

void ProPresetManager::savePreset()
{
	MemoryBlock destinationData;
	mProcessor->getStateInformation(destinationData);

	mCurrentlyLoadedPreset.deleteFile();

	mCurrentlyLoadedPreset.appendData(destinationData.getData(), destinationData.getSize());

	mCurrentPresetIsSaved = true;
}

void ProPresetManager::saveAsPreset(String inPresetName)
{
	File presetFile = File(mPresetDirectory + directorySeperator + inPresetName + PRESET_FILE_EXTENSION);

	if (!presetFile.exists())
	{
		presetFile.create();
	}
	else
	{
		presetFile.deleteFile();
	}

	MemoryBlock destinationData;
	mProcessor->getStateInformation(destinationData);

	presetFile.appendData(destinationData.getData(), destinationData.getSize());

	mCurrentPresetIsSaved = true;
	mCurrentPresetName = inPresetName;

	storeLocalPresets();
}

void ProPresetManager::loadPreset(int inPresetIndex)
{
	mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];

	MemoryBlock presetBinary;

	if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary))
	{
		mCurrentPresetIsSaved = true;
		mCurrentPresetName = getPresetName(inPresetIndex);
		mProcessor->setStateInformation(presetBinary.getData(), presetBinary.getSize());
	}
}

bool ProPresetManager::getIsCurrentPresetSaved()
{
	return mCurrentPresetIsSaved;
}

String ProPresetManager::getCurrentPresetName()
{
	return mCurrentPresetName;
}

void ProPresetManager::storeLocalPresets()
{
	mLocalPresets.clear();

	for (DirectoryIterator di(File(mPresetDirectory),
		false,
		"*" + (String)PRESET_FILE_EXTENSION,
		File::TypesOfFileToFind::findFiles); di.next();)
	{
		File preset = di.getFile();
		mLocalPresets.add(preset);
	}
}