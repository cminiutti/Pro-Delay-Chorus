/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ProMainPanel.h"

//==============================================================================
class ProPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:

    ProPluginAudioProcessorEditor (ProPluginAudioProcessor&);
    ~ProPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
   
    ProPluginAudioProcessor& processor;

	ScopedPointer<ProMainPanel> mMainPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProPluginAudioProcessorEditor)
};
