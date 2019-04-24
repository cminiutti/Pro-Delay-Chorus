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
	const int numParameters = mProcessor->getNumParameters();

	for (int i = 0; i < numParameters; i++)
	{
		inElement->setAttribute(mProcessor->getParameterName(i),
								mProcessor->getParameter(i));
	}
}

void ProPresetManager::loadPresetForXml(XmlElement* inElement)
{
	mCurrentPresetXml = inElement;

	for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++)
	{
		const String name = mCurrentPresetXml->getAttributeName(i);
		const float value = mCurrentPresetXml->getDoubleAttribute(name);

		for (int j = 0; j < mProcessor->getNumParameters(); j++)
		{
			if (mProcessor->getParameterName(j) == name)
			{
				mProcessor->setParameterNotifyingHost(j, value);
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
	const int numParameters = mProcessor->getNumParameters();

	for (int i = 0; i < numParameters; i++)
	{
		mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
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