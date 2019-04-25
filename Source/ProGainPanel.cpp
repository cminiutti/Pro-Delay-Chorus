/*
  ==============================================================================

    ProGainPanel.cpp
    Created: 4 Apr 2019 3:15:36pm
    Author:  minut

  ==============================================================================
*/

#include "ProGainPanel.h"
#include "ProParameters.h"
#include "ProHelperFunctions.h"

ProGainPanel::ProGainPanel(ProPluginAudioProcessor* inProcessor)
	: ProPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);

	const int meter_width = 64;
	mVuMeter = new ProVuMeter(mProcessor);
	mVuMeter->setBounds((getWidth() * 0.5) - (meter_width * 0.5), (getHeight() * 0.55) - (meter_width * 0.5), meter_width, getHeight() * 0.45);
	addAndMakeVisible(mVuMeter);
}

ProGainPanel::~ProGainPanel()
{

}

void ProGainPanel::paint(Graphics& g)
{
	ProPanelBase::paint(g);

	if (mKnob)
		paintComponentLabel(g, mKnob);
}

void ProGainPanel::setParameterID(int inParameterID)
{
	mKnob = new ProParameterKnob(mProcessor->parameters, ProParameterID[inParameterID], ProParameterLabel[inParameterID]);

	const int sliderSize = 54;

	mKnob->setBounds(getWidth() * 0.5 - sliderSize * 0.5, getHeight() * 0.20 - sliderSize * 0.5, sliderSize, sliderSize);
	addAndMakeVisible(mKnob);

	mVuMeter->setParameterID(inParameterID);
}