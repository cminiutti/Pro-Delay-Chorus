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
	/*// Highlight panels when mouse is hovering over
	if (isMouseOver(true))
	{
		const Colour hoverColour =
		Colour(Colours::black).withAlpha(0.4f);

		g.setColour(hoverColour);
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