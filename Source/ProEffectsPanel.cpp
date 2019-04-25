/*
  ==============================================================================

    ProEffectsPanel.cpp
    Created: 4 Apr 2019 3:15:30pm
    Author:  minut

  ==============================================================================
*/

#include "ProEffectsPanel.h"
#include "ProParameters.h"
#include "ProHelperFunctions.h"

ProEffectsPanel::ProEffectsPanel(ProPluginAudioProcessor* inProcessor)
	:	ProPanelBase(inProcessor)
{
	setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);

	const int currentStyle = static_cast<int> (*mProcessor->parameters.getRawParameterValue("Type"));

	setEffectsPanelStyle((ProEffectsPanelStyle)currentStyle);
}

ProEffectsPanel::~ProEffectsPanel()
{

}

void ProEffectsPanel::paint(Graphics& g)
{
	ProPanelBase::paint(g);

	String label;

	switch (mStyle)
	{
		case pProEffectsPanelStyle_Delay:
		{
			label = "DELAY";
		} break;

		case pProEffectsPanelStyle_Chorus:
		{
			label = "CHORUS";
		} break;

		default:
		case(pProEffectsPanelStyle_TotalNumStyles):
		{
			jassertfalse;
		} break;
	}

	g.setColour(ProColour_5);
	g.setFont(font_3);

	g.drawText(label, 0, 0, getWidth(), 80, Justification::centred);

	for (int i = 0; i < mKnobs.size(); i++)
	{
		paintComponentLabel(g, mKnobs[i]);
	}
}

void ProEffectsPanel::setEffectsPanelStyle(ProEffectsPanelStyle inStyle)
{
	mStyle = inStyle;

	mKnobs.clear();

	const int knobSize = 56;
	int x = 130;
	int y = getHeight() * 0.5 - knobSize * 0.5;

	switch (mStyle)
	{
	case pProEffectsPanelStyle_Delay:
	{
		ProParameterKnob* time = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_DelayTime], ProParameterLabel[pParameter_DelayTime]);
		time->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(time);
		mKnobs.add(time);

		x += (knobSize * 2);

		ProParameterKnob* feedback = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_DelayFeedback], ProParameterLabel[pParameter_DelayFeedback]);
		feedback->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(feedback);
		mKnobs.add(feedback);

		x += (knobSize * 2);

		ProParameterKnob* wetdry = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_DelayWetDry], ProParameterLabel[pParameter_DelayWetDry]);
		wetdry->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(wetdry);
		mKnobs.add(wetdry);

	} break;

	case pProEffectsPanelStyle_Chorus:
	{
		ProParameterKnob* rate = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_ModulationRate], ProParameterLabel[pParameter_ModulationRate]);
		rate->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(rate);
		mKnobs.add(rate);

		x += (knobSize * 2);

		ProParameterKnob* depth = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_ModulationDepth], ProParameterLabel[pParameter_ModulationDepth]);
		depth->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(depth);
		mKnobs.add(depth);

		x += (knobSize * 2);

		ProParameterKnob* wetdry = new ProParameterKnob(mProcessor->parameters, ProParameterID[pParameter_DelayWetDry], ProParameterLabel[pParameter_DelayWetDry]);
		wetdry->setBounds(x, y, knobSize, knobSize);
		addAndMakeVisible(wetdry);
		mKnobs.add(wetdry);
	} break;

	case pProEffectsPanelStyle_TotalNumStyles:
	{
		jassertfalse;
	} break;
	}

	repaint();
}

void ProEffectsPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	ProEffectsPanelStyle style = (ProEffectsPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();

	setEffectsPanelStyle(style);
}