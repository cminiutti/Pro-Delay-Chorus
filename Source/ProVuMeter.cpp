/*
  ==============================================================================

    ProVuMeter.cpp
    Created: 24 Apr 2019 12:28:33pm
    Author:  minut

  ==============================================================================
*/

#include "ProVuMeter.h"
#include "ProInterfaceDefines.h"
#include "ProParameters.h"

ProVuMeter::ProVuMeter(ProPluginAudioProcessor* inProcessor)
	: mParameterID(-1), mCh0Level(0), mCh1Level(0), mProcessor(inProcessor)
{

}

ProVuMeter::~ProVuMeter()
{

}

void ProVuMeter::paint(Graphics& g)
{
	const int meter_width = getWidth() / 3;

	g.setColour(ProColour_6);
	g.fillRect(0, 0, meter_width, getHeight());
	g.fillRect(meter_width * 2, 0, meter_width, getHeight());

	int ch0fill = getHeight() - (getHeight() * mCh0Level);
	int ch1fill = getHeight() - (getHeight() * mCh1Level);

	if (ch0fill < 0)
	{
		ch0fill = 0;
	}

	if (ch1fill < 0)
	{
		ch1fill = 0;
	}

	g.setColour(ProColour_7);
	g.fillRect(0, ch0fill, meter_width, getHeight());
	g.fillRect(meter_width * 2, ch1fill, meter_width, getHeight());
}

void ProVuMeter::timerCallback()
{
	float updatedCh0Level = 0.0f;
	float updatedCh1Level = 0.0f;

	switch (mParameterID)
	{
		case (pParameter_InputGain):
		{
			updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getInputGainMeterLevel(1);
		} break;
		case (pParameter_OutputGain):
		{
			updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);
		} break;
	}

	if (updatedCh0Level > mCh0Level)
	{
		mCh0Level = updatedCh0Level;
	}
	else
	{
		mCh0Level = ProMeterSmoothingCoefficient * (mCh0Level - updatedCh0Level) + updatedCh0Level;
	}

	if (updatedCh1Level > mCh1Level)
	{
		mCh1Level = updatedCh1Level;
	}
	else
	{
		mCh1Level = ProMeterSmoothingCoefficient * (mCh1Level - updatedCh1Level) + updatedCh1Level;
	}

	mCh0Level = pro_denormalize(mCh0Level);
	mCh1Level = pro_denormalize(mCh1Level);

	if (mCh0Level && mCh1Level)
	{
		repaint();
	}
}

void ProVuMeter::setParameterID(int inParameterID)
{
	mParameterID = inParameterID;

	startTimerHz(15);
}
