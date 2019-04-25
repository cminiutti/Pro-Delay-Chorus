/*
  ==============================================================================

    ProPanelBase.cpp
    Created: 4 Apr 2019 3:14:51pm
    Author:  minut

  ==============================================================================
*/

#include "ProPanelBase.h"

ProPanelBase::ProPanelBase(ProPluginAudioProcessor* inProcessor)
	: mProcessor(inProcessor)
{

}

ProPanelBase::~ProPanelBase()
{

}

void ProPanelBase::paint(Graphics &g)
{
	/*g.setColour(Colours::purple);
	g.fillAll();

	g.setColour(Colours::black);
	g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 4, 2);*/

	// Highlight panels when mouse is hovering over
	/*if (isMouseOver())
	{
		g.setColour(ProColour_4);
		g.fillAll();
	}*/
}

void ProPanelBase::mouseEnter(const MouseEvent& event)
{
	repaint();
}

void ProPanelBase::mouseExit(const MouseEvent& event)
{
	repaint();
}