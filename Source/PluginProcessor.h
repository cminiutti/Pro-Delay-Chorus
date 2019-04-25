/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ProGain.h"
#include "ProDelay.h"
#include "ProLFO.h"

#include "ProPresetManager.h"

//==============================================================================
class ProPluginAudioProcessor  : public AudioProcessor
{
public:

    //==============================================================================
    ProPluginAudioProcessor();
    ~ProPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	float getInputGainMeterLevel(int inChannel);
	float getOutputGainMeterLevel(int inChannel);

	AudioProcessorValueTreeState parameters;

	ProPresetManager* getPresetManager()
	{
		return mPresetManager;
	}

private:

	void initializeDSP();
	void initializeParameters();

	std::unique_ptr<ProGain> mInputGain[2];
	std::unique_ptr<ProGain> mOutputGain[2];
	std::unique_ptr<ProDelay> mDelay[2];
	std::unique_ptr<ProLFO> mLFO[2];

	ScopedPointer<ProPresetManager> mPresetManager;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProPluginAudioProcessor)
};
