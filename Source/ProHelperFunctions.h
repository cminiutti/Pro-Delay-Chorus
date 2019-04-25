/*
  ==============================================================================

    ProHelperFunctions.h
    Created: 10 Apr 2019 1:36:08pm
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ProInterfaceDefines.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
	const int x = inComponent->getX() - (inComponent->getWidth() * 0.25f);
	const int y = inComponent->getY() + inComponent->getHeight();
	const int w = inComponent->getWidth() * 1.5f;
	const int h = 20;

	const float cornersize = 3.0f;

	const String label = inComponent->getName();

	g.setColour(ProColour_3);
	g.fillRoundedRectangle(x, y, w, h, cornersize);


	g.setColour(ProColour_1);
	g.setFont(font_1);

	g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}