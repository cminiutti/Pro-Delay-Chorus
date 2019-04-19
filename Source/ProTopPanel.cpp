/*
  ==============================================================================

    ProTopPanel.cpp
    Created: 4 Apr 2019 3:15:54pm
    Author:  minut

  ==============================================================================
*/

#include "ProTopPanel.h"

ProTopPanel::ProTopPanel(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

ProTopPanel::~ProTopPanel()
{

}

void ProTopPanel::paint(Graphics& g)
{
	ProPanelBase::paint(g);

	g.drawFittedText("PRO AUDIO PLUGIN", 0, 0, getWidth() - 10, getHeight() - 10, Justification::centredRight, 1);
}