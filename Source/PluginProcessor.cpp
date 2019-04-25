/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ProParameters.h"

//==============================================================================
ProPluginAudioProcessor::ProPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	parameters(*this, nullptr, "PARAMETERS", 
		{
			std::make_unique<AudioParameterFloat>("InputGain", "InputGain", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("OutputGain", "OutputGain", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("Time", "Time", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("Feedback", "Feedback", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("WetDry", "WetDry", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("Type", "Type", NormalisableRange<float>(0.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("ModulationRate", "ModulationRate", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
			std::make_unique<AudioParameterFloat>("ModulationDepth", "ModulationDepth", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
		})
#endif
{
	//initializeParameters();
	initializeDSP();

	mPresetManager = new ProPresetManager(this);
}

ProPluginAudioProcessor::~ProPluginAudioProcessor()
{
}

//==============================================================================
void ProPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	for (int i = 0; i < 2; i++)
	{
		mDelay[i]->setSampleRate(sampleRate);
		mLFO[i]->setSampleRate(sampleRate);
	}
}

void ProPluginAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());


	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		mInputGain[channel]->process(channelData,
			*parameters.getRawParameterValue("InputGain"),
			channelData,
			buffer.getNumSamples());

		// Pass LFO to only 1 channel to create stereo width
		float rate = (channel == 0) ? *parameters.getRawParameterValue("ModulationRate") : 0.0f;

		mLFO[channel]->process(rate,
			*parameters.getRawParameterValue("ModulationDepth"),
			buffer.getNumSamples());

		mDelay[channel]->process(channelData,
			*parameters.getRawParameterValue("Time"),
			*parameters.getRawParameterValue("Feedback"),
			*parameters.getRawParameterValue("WetDry"),
			*parameters.getRawParameterValue("Type"),
			mLFO[channel]->getBuffer(),
			channelData,
			buffer.getNumSamples());

		mOutputGain[channel]->process(channelData,
			*parameters.getRawParameterValue("OutputGain"),
			channelData,
			buffer.getNumSamples());
	}
}

//==============================================================================
const String ProPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String ProPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void ProPluginAudioProcessor::releaseResources()
{
	for (int i = 0; i < 2; i++)
	{
		mDelay[i]->reset();
		mLFO[i]->reset();
	}
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool ProPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProPluginAudioProcessor::createEditor()
{
    return new ProPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ProPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	XmlElement preset("Pro_StateInfo");

	XmlElement* presetBody = new XmlElement("ProPreset");

	mPresetManager->getXmlForPreset(presetBody);

	preset.addChildElement(presetBody);
	copyXmlToBinary(preset, destData);
}

void ProPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	XmlElement* xmlState = getXmlFromBinary(data, sizeInBytes);

	if (xmlState) 
	{
		forEachXmlChildElement(*xmlState, subChild)
		{
			mPresetManager->loadPresetForXml(subChild);
		}
	}
	else
	{
		jassertfalse;
	}
}

float ProPluginAudioProcessor::getInputGainMeterLevel(int inChannel)
{
	const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

float ProPluginAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
	const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

void ProPluginAudioProcessor::initializeParameters()
{
	for (int i = 0; i < pParameter_TotalNumParameters; i++)
	{
		parameters.createAndAddParameter(ProParameterID[i],
										 ProParameterID[i],
										 ProParameterID[i],
										 NormalisableRange<float>(0.0f, 1.0f),
										 0.5f,
										 nullptr,
										 nullptr);
	}
}

void ProPluginAudioProcessor::initializeDSP()
{
	for (int i = 0; i < 2; i++)
	{
		mInputGain[i] = std::make_unique<ProGain>(ProGain());
		mOutputGain[i] = std::make_unique<ProGain>(ProGain());
		mDelay[i] = std::make_unique<ProDelay>(ProDelay());
		mLFO[i] = std::make_unique<ProLFO>(ProLFO());
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProPluginAudioProcessor();
}
