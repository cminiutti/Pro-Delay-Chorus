/*
  ==============================================================================

    ProMainPanel.cpp
    Created: 4 Apr 2019 3:14:59pm
    Author:  minut

  ==============================================================================
*/

#include "ProMainPanel.h"
#include "ProParameters.h"

ProMainPanel::ProMainPanel(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

	mTopPanel = new ProTopPanel(inProcessor);
	mTopPanel->setTopLeftPosition(0, 0);
	addAndMakeVisible(mTopPanel);

	mInputGainPanel = new ProGainPanel(inProcessor);
	mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
	mInputGainPanel->setParameterID(pParameter_InputGain);
	addAndMakeVisible(mInputGainPanel);

	mOutputGainPanel = new ProGainPanel(inProcessor);
	mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	mOutputGainPanel->setParameterID(pParameter_OutputGain);
	addAndMakeVisible(mOutputGainPanel);

	mCenterPanel = new ProCenterPanel(inProcessor);
	mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	addAndMakeVisible(mCenterPanel);
}

ProMainPanel::~ProMainPanel()
{

}