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

	mLookAndFeel = new ProLookAndFeel();
	setLookAndFeel(mLookAndFeel);

	LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);

	mBackgroundImage = ImageCache::getFromMemory(BinaryData::kadenze_bg_png, BinaryData::kadenze_bg_pngSize);
}

ProPluginAudioProcessorEditor::~ProPluginAudioProcessorEditor()
{
}

//==============================================================================
void ProPluginAudioProcessorEditor::paint (Graphics& g)
{
	g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void ProPluginAudioProcessorEditor::resized()
{

}
