/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProPluginAudioProcessorEditor::ProPluginAudioProcessorEditor (ProPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

	mMainPanel = new ProMainPanel(&processor);
	addAndMakeVisible(mMainPanel);
}

ProPluginAudioProcessorEditor::~ProPluginAudioProcessorEditor()
{
}

//==============================================================================
void ProPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void ProPluginAudioProcessorEditor::resized()
{

}
